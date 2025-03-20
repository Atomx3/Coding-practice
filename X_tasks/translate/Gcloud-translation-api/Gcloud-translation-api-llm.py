# Description: This script uses Google Cloud Translation API with Language Model (Translation LLM) to translate text files in a directory to a target language.
import os
import logging
import time
import random
from google.cloud import translate_v3 as translate
from google.oauth2 import service_account
import mimetypes
from google.api_core.exceptions import ResourceExhausted
from ratelimit import limits, sleep_and_retry
import unicodedata
import string
from langdetect import detect, LangDetectException
import re
import yaml

# --- Configuration ---
PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = "us-central1" # "global" 
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "general/translation-llm" # "general/base" # 
SOURCE_LANG = "zh-CN"
TARGET_LANG = "en"
TARGET_DIR_NAME = "en"
MIME_TYPE = "text/plain"
VOCABULARY_ID = None
# Rate limiting to control API call frequency
CALLS_PER_MINUTE = 15
ONE_MINUTE = 60
INITIAL_RETRY_DELAY = 2
MAX_RETRIES = 5

# meet the "unexpected language" files, decide whether to translate 
TRANSLATE_UNEXPECTED_LANGUAGES = True  # true means translate anyway, false means skip


def detect_language(text):
    """Detects the language of the text using langdetect."""
    try:
        return detect(text)
    except LangDetectException:
        return "unknown"

# --- Translation Prompt Template (Not used, but kept for consistency) ---
TRANSLATION_PROMPT = """Translate the following content from {source_lang} to {target_lang}. This is a {file_type} file, and preserving the original formatting is critical.

**ABSOLUTELY CRITICAL INSTRUCTIONS:**

1. **Preserve ALL Formatting:** Maintain *every* aspect of the original formatting. This includes, but is not limited to:
    * Markdown syntax (headings, lists, links, bold, italics, code blocks, etc.)
    * Spacing (line breaks, indentation).
    * Any other file-type-specific formatting.
    * DO NOT add, remove, or alter any formatting elements.

2. **File/Directory Names:** Do NOT translate file names or directory names. Keep them in English.

3. **YAML Front Matter:**
    * Keep keywords in English: title, date, description, categories, tags
    * Translate values simply and directly after the keywords.
    * Keep YAML structure (indentation, keys, values, lists) if present in a Markdown header or as a separate `.yaml` file.

4. **Tone and Style:** Maintain the original tone and style of the text while ensuring the translation is culturally appropriate for the target language, And keep the translation style consistent.

Input Text:
"""

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# --- Environment validation ---
REQUIRED_ENV_VARS = ["GOOGLE_CLOUD_PROJECT", "GOOGLE_APPLICATION_CREDENTIALS"]
missing_vars = [var for var in REQUIRED_ENV_VARS if os.environ.get(var) is None]
if missing_vars:
    logging.error(f"Missing required environment variables: {', '.join(missing_vars)}")
    exit(1)

# --- Initialize Google Cloud services ---
try:
    credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
    translate_client = translate.TranslationServiceClient(credentials=credentials)
    logging.info("Successfully initialized Translation API client.")
    
except Exception as e:
    logging.error(f"Error initializing services: {str(e)}")
    exit(1)

def get_file_type(file_path):
    """Determines file type."""
    file_extension = os.path.splitext(file_path)[1].lower()
    mime_type, _ = mimetypes.guess_type(file_path)
    if file_extension == ".md": return "markdown"
    if file_extension == ".yaml" or mime_type == "text/x-yaml": return "yaml"
    if file_extension == ".txt" or (mime_type and mime_type.startswith("text/")): return "text"
    return "unknown"

@sleep_and_retry
@limits(calls=CALLS_PER_MINUTE, period=ONE_MINUTE)
def translate_text_with_llm(text, target_lang, file_type, client):
    """Translates text using Translation LLM."""
    if not text:
        return ""

    parent = f"projects/{PROJECT_ID}/locations/{LOCATION}"
    contents = [text]
    target_language_code = target_lang
    mime_type_for_api = MIME_TYPE

    request = translate.TranslateTextRequest(
        parent=parent,
        contents=contents,
        mime_type=mime_type_for_api,
        source_language_code=SOURCE_LANG,
        target_language_code=target_language_code,
        model=f"projects/{PROJECT_ID}/locations/{LOCATION}/models/{MODEL_NAME}"
    )

    if VOCABULARY_ID:
        request.glossary_config = translate.TranslateTextGlossaryConfig(glossary=VOCABULARY_ID)

    for attempt in range(MAX_RETRIES):
        try:
            response = client.translate_text(request=request)
            return response.translations[0].translated_text
        except ResourceExhausted:
            delay = INITIAL_RETRY_DELAY * (2 ** attempt)
            logging.info(f"Rate limit hit, waiting {delay} seconds before retry...")
            time.sleep(delay)
            continue
    try:
        response = client.translate_text(request=request)
        translated_text = response.translations[0].translated_text
        logging.info(f"LLM translated content: {translated_text}")  # add logging
        return translated_text
    except Exception as e:
        logging.error(f"Translation LLM error: {e}")
        return None


def preprocess_file_type(content):
    """Removes metadata and code snippets from content, preserving format elements."""
    # Remove code blocks
    content = re.sub(r'```.*?```', '', content, flags=re.DOTALL)
    
    # Remove inline code
    content = re.sub(r'`.*?`', '', content)
    
    # Remove HTML tags
    content = re.sub(r'<[^>]*>', '', content)
    
    # Remove Markdown links but keep the text
    content = re.sub(r'\[([^\]]+)\]\([^)]+\)', r'\1', content)
    
    # Remove Markdown formatting symbols
    content = re.sub(r'[*_#>~|]', '', content)
    
    # Remove YAML frontmatter
    content = re.sub(r'^---\n.*?\n---\n', '', content, flags=re.DOTALL)
    
    # Remove YAML syntax
    content = re.sub(r'[-:{}[\]"]', ' ', content)
    
    # Remove extra whitespace
    content = re.sub(r'\s+', ' ', content).strip()
    
    return content

def is_already_translated(file_path, TARGET_LANG):
    """Checks if file needs translation based on language detection using langdetect."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()

        # Preprocess content to remove formatting elements before language detection
        processed_content = preprocess_file_type(content)
        
        if not processed_content.strip():
            logging.warning(f"File: {file_path}, No content after preprocessing.")
            return False  # Empty content after preprocessing, default to translation
        
        # Detect actual source language
        try:
            Actual_SOURCE_LANG = detect(processed_content)
            logging.info(f"File: {file_path}, Detected language: {Actual_SOURCE_LANG}")
        except LangDetectException as e:
            logging.warning(f"File: {file_path}, Language detection error: {e}")
            return False  # Language detection failed, default to translation
        
        # Skip translation only if the detected language is the target language
        if Actual_SOURCE_LANG == TARGET_LANG:
            logging.info(f"File: {file_path}, Content is already in {TARGET_LANG}, skipping translation.")
            return True
        else:
            logging.info(f"File: {file_path}, Content language is {Actual_SOURCE_LANG}, needs translation to {TARGET_LANG}.")
            return False

    except Exception as e:
        logging.warning(f"Could not process {file_path}, will attempt translation. Error: {e}")
        return False  # Default to translation on error
    
def process_files(current_dir, client):
    """Processes files for translation."""
    target_dir = os.path.join(current_dir, TARGET_DIR_NAME)
    if not os.path.exists(target_dir):
        logging.error(f"Target directory '{target_dir}' does not exist.")
        return

    for root, _, files in os.walk(target_dir):
        for filename in files:
            file_path = os.path.join(root, filename)
            file_type = get_file_type(file_path)

            print(f"File: {file_path}, Type: {file_type}")

            if file_type == "unknown":
                logging.warning(f"Skipping unknown file type: {file_path}")
                continue

            logging.info(f"Processing file: {file_path}")

            if is_already_translated(file_path, TARGET_LANG):
                continue

            retries = 5
            delay = 1
            translated_text = None

            for attempt in range(retries):
                try:
                    with open(file_path, 'r', encoding='utf-8') as f:
                        content = f.read()

                    translated_text = translate_text_with_llm(content, TARGET_LANG, file_type, client) # pass client here
                    if translated_text:
                        break

                except ResourceExhausted as e:
                    logging.warning(f"Rate limit exceeded. Attempt {attempt + 1}/{retries}. Retrying in {delay} seconds...")
                    time.sleep(delay + random.uniform(0, 1))
                    delay *= 2
                except Exception as e:
                    logging.error(f"Error processing {file_path}: {e}")
                    break

            if translated_text:
                try:
                    with open(file_path, 'w', encoding='utf-8') as tf:
                        tf.write(translated_text)
                    logging.info(f"Translated {file_path} and saved.")
                except Exception as e:
                    logging.error(f"Error writing to {file_path}: {e}")
            else:
                logging.error(f"Translation failed for {file_path} after {retries} attempts.")

if __name__ == "__main__":
    current_directory = os.getcwd()
    logging.info("Starting translation process...")
    process_files(current_directory, translate_client) # pass client here
    logging.info("Translation process completed.")
