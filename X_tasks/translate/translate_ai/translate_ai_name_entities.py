# prevents the gRPC warning message
import os
os.environ['GRPC_ENABLE_FORK_SUPPORT'] = '0'

import logging
import time
import random
from google.cloud import aiplatform
from google.oauth2 import service_account
from vertexai.preview.generative_models import GenerativeModel, Part, SafetySetting
import mimetypes
from google.api_core.exceptions import ResourceExhausted
from ratelimit import limits, sleep_and_retry
import unicodedata

# --- Configuration ---
PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = os.environ.get("GOOGLE_CLOUD_REGION", "europe-west3")
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "gemini-1.5-pro-001"
SOURCE_LANG = "zh-CN"
TARGET_LANG = "en"
TARGET_DIR_NAME = "en"
MAX_OUTPUT_TOKENS = 8192
TEMPERATURE = 0.9
TOP_P = 0.8

# --- Translation Prompt Template ---
TRANSLATION_PROMPT = """Translate the following content from {source_lang} to {target_lang}. This is a {file_type} file, and preserving the original formatting is critical.

**ABSOLUTELY CRITICAL INSTRUCTIONS:**

1. **Preserve ALL Formatting:** Maintain *every* aspect of the original formatting. This includes, but is not limited to:
    * Markdown syntax (headings, lists, links, bold, italics, code blocks, etc.)
    * YAML structure (indentation, keys, values, lists) if present in a Markdown header or as a separate `.yaml` file.
    * Spacing (line breaks, indentation).
    * Any other file-type-specific formatting.
    * DO NOT add, remove, or alter any formatting elements.

2. **Named Entities:** Translate named entities as follows:
    * Include the original text in the source language.
    * Provide the Pinyin (for Chinese) or Romanization (for other languages) of the original text.
    * Provide the translation in the target language.
    * This only applies to Chinese language: organization names, personal names, place names, book titles, movie titles, Chinese idioms (成语典故), proverbs, allegorical phrases (歇后语), and famous Cultural phrases and proper nouns.
    * example: 近朱者赤，近墨者黑. (Jìn zhū zhě chì, jìn mò zhě hēi.) He who walks with the wise grows wise, but a companion of fools suffers harm.
    * Note: Only use this named entities method for well-known or culturally significant in Chinese context. Avoid applying this to all words and sentences.

3. **File/Directory Names:** Do NOT translate file names or directory names. Keep them in English.

4. **YAML Front Matter:**
    * Keep keywords in English: title, date, description, categories, tags
    * Translate values simply and directly
    * For tags/categories: translate to single clear terms without pinyin

5. **Tone and Style:** Maintain the original tone and style of the text while ensuring the translation is culturally appropriate for the target language, And keep the translation style consistent.

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
    aiplatform.init(project=PROJECT_ID, location=LOCATION, credentials=credentials)
    model = GenerativeModel(MODEL_NAME)
    logging.info(f"Successfully initialized {MODEL_NAME} model.")
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


# Rate limiting to control API call frequency
CALLS_PER_MINUTE = 15  # Adjust based on your quota
ONE_MINUTE = 60
INITIAL_RETRY_DELAY = 2
MAX_RETRIES = 5
@sleep_and_retry
@limits(calls=CALLS_PER_MINUTE, period=ONE_MINUTE)


def translate_text_with_gemini(text, target_lang, file_type="text", model=model):
    """Translates text using Gemini."""
    if not text:
        return ""
        
    prompt = TRANSLATION_PROMPT.format(
        file_type=file_type,
        source_lang=SOURCE_LANG,
        target_lang=target_lang
    )
    for attempt in range(MAX_RETRIES):  # Insert here, before the try block
        try:
            response = model.generate_content(
                [Part.from_text(prompt), Part.from_text(text)],
                generation_config={
                    "max_output_tokens": MAX_OUTPUT_TOKENS,
                    "temperature": TEMPERATURE,
                    "top_p": TOP_P,
                },
                safety_settings=[
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_HATE_SPEECH, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_DANGEROUS_CONTENT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_SEXUALLY_EXPLICIT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_HARASSMENT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                ]
            )
            return response.text.encode('utf-8').decode('utf-8') if response and response.text else None
        except ResourceExhausted:
            delay = INITIAL_RETRY_DELAY * (2 ** attempt)
            logging.info(f"Rate limit hit, waiting {delay} seconds before retry...")
            time.sleep(delay)
            continue
    try:
        response = model.generate_content(
            [Part.from_text(prompt), Part.from_text(text)],
            generation_config={
                "max_output_tokens": MAX_OUTPUT_TOKENS,
                "temperature": TEMPERATURE,
                "top_p": TOP_P,
            },
            safety_settings=[
                SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_HATE_SPEECH, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_DANGEROUS_CONTENT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_SEXUALLY_EXPLICIT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_HARASSMENT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
            ]
        )
        return response.text.encode('utf-8').decode('utf-8') if response and response.text else None
    except Exception as e:
        logging.error(f"Gemini translation error: {e}")
        return None

def is_already_translated(file_path, target_lang):
    """Checks if file is already translated using Unicode character classification."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        target_chars = sum(1 for char in content if unicodedata.category(char).startswith('L'))
        valid_chars = len(content)
        
        if valid_chars > 0 and target_chars / valid_chars > 0.9:
            logging.info(f"Skipping {file_path} (appears to be already translated).")
            return True
        return False
    except Exception as e:
        logging.warning(f"Could not read {file_path}, will attempt translation. Error: {e}")
        return False


def process_files(current_dir):
    """Processes files for translation."""
    target_dir = os.path.join(current_dir, TARGET_DIR_NAME)
    if not os.path.exists(target_dir):
        logging.error(f"Target directory '{target_dir}' does not exist.")
        return

    for root, _, files in os.walk(target_dir):
        for filename in files:
            file_path = os.path.join(root, filename)
            file_type = get_file_type(file_path)

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
                    
                    translated_text = translate_text_with_gemini(content, TARGET_LANG, file_type, model)
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
    process_files(current_directory)
    logging.info("Translation process completed.")
