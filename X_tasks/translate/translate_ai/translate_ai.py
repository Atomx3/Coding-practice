import os
import logging
import re
import traceback
import time  # Import the time module
import random # Import for random jitter
from google.cloud import aiplatform
from google.oauth2 import service_account
from vertexai.preview.generative_models import GenerativeModel, Part, SafetySetting
import mimetypes
from google.api_core.exceptions import ResourceExhausted  # Import the exception

# --- Configuration ---
PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = os.environ.get("GOOGLE_CLOUD_REGION", "europe-west3")
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "gemini-1.5-pro-001"  # Use Gemini 1.5 Pro
SOURCE_LANG = "zh-CN"
TARGET_LANG = "en"
TARGET_DIR_NAME = "en"
MAX_OUTPUT_TOKENS = 8192
TEMPERATURE = 0.2
TOP_P = 0.9

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

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

# --- Helper functions ---

def get_file_type(file_path):
    """Determines the file type based on its extension and MIME type."""
    file_extension = os.path.splitext(file_path)[1].lower()
    mime_type, _ = mimetypes.guess_type(file_path)
    logging.debug(f"File extension: {file_extension}, MIME type: {mime_type} for file: {file_path}")

    if file_extension == ".md":
        return "markdown"
    elif file_extension == ".yaml" or mime_type == "text/x-yaml":
        return "yaml"
    elif file_extension == ".txt" or (mime_type and mime_type.startswith("text/")):
        return "text"
    else:
        return "unknown"

def extract_yaml_header(text):
    """Extracts the YAML header from a Markdown file."""
    header_start = text.find("---")
    return "" if header_start == -1 else text[header_start:text.find("---", header_start + 1) + 3] if text.find("---", header_start + 1) != -1 else text

def extract_content_after_header(text):
    """Extracts the content after the YAML header."""
    header_end = text.find("---", text.find("---") + 1)
    return text if header_end == -1 else text[header_end + 3:]

def translate_yaml_values(yaml_header, target_lang, model=model):
    """Translates YAML values, preserving keys, and handling lists."""
    lines = yaml_header.splitlines()
    translated_lines = []
    for line in lines:
        if ":" in line:
            key, value = line.split(":", 1)
            key = key.strip()
            value = value.strip()
            if key in ["title", "date", "description", "categories", "tags"]:
                translated_lines.append(line)
            else:
                # Handle list items within YAML values
                if value.startswith("-"):
                    items = [item.strip() for item in value.split("-") if item.strip()]
                    translated_items = []
                    for item in items:
                        prompt = f"Translate the following from {SOURCE_LANG} to {target_lang}: {item}"
                        try:
                            response = model.generate_content(
                                [Part.from_text(prompt)],
                                generation_config={"temperature": TEMPERATURE, "top_p": TOP_P, "max_output_tokens": MAX_OUTPUT_TOKENS}
                            )
                            translated_items.append(response.text if response and response.text else item)
                        except Exception as e:
                            logging.error(f"Error translating YAML list item: {item}: {e}")
                            translated_items.append(item)
                    translated_value = "- " + "\n- ".join(translated_items)
                    translated_lines.append(f"{key}: {translated_value}")

                else:
                    # Regular key-value translation
                    prompt = f"Translate the following from {SOURCE_LANG} to {target_lang}: {value}"
                    try:
                        response = model.generate_content(
                            [Part.from_text(prompt)],
                            generation_config={"temperature": TEMPERATURE, "top_p": TOP_P, "max_output_tokens": MAX_OUTPUT_TOKENS}
                        )
                        translated_lines.append(f"{key}: {response.text if response and response.text else value}")
                    except Exception as e:
                        logging.error(f"Error translating YAML value: {value}: {e}")
                        translated_lines.append(line)
        else:
            translated_lines.append(line)  # Non key-value lines (e.g., ---)
    return "\n".join(translated_lines)

def translate_text_with_gemini(text, target_lang, file_type="text", model=model):
    """Translates text with Gemini, handling retries and rate limits."""
    if not text:
        return ""

    prompt = f"""Translate the following {file_type} content from {SOURCE_LANG} to {target_lang}.

**Critical Instructions:**

*   **Preserve ALL original formatting:**  Do not add, remove, or change formatting.
*   **Named Entities:** Use: `[Original Text Pinyin/Romanization] Translated Text`.
*   **File/Directory Names:** Do NOT translate file/directory names.
*   **Output ONLY the translated text:** No explanations.
*   **Maintain Tone and Style:** Preserve tone/style, ensuring cultural appropriateness.
"""
    try:
        prompt = prompt.encode('utf-8').decode('utf-8')
        text = text.encode('utf-8').decode('utf-8')

        # --- Exponential Backoff Implementation ---
        retries = 5  # Maximum number of retries
        delay = 1  # Initial delay in seconds

        for attempt in range(retries):
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

                if not response or not response.text:
                    logging.warning(f"Received empty response from Gemini. Attempt {attempt + 1}/{retries}")
                    if attempt == retries - 1:  # Last attempt
                        return None
                    continue #try again

                return response.text.encode('utf-8').decode('utf-8')

            except ResourceExhausted as e:  # Catch the specific rate limit error
                logging.warning(f"Rate limit exceeded. Attempt {attempt + 1}/{retries}.  Retrying in {delay} seconds...")
                time.sleep(delay + random.uniform(0, 1))  # Add random jitter
                delay *= 2  # Exponential backoff
            except Exception as e: # other exceptions
                logging.error(f"Translation error: {e}")
                logging.error(traceback.format_exc())
                return None

        logging.error(f"Translation failed after {retries} attempts.") #log if all retries failed
        return None

    except Exception as e:
        logging.error(f"Outer exception: {e}")  # Catch any other exceptions
        logging.error(traceback.format_exc())
        return None

def is_already_translated(file_path, target_lang):
    """Checks if the file is likely already translated into the target language (robust)."""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()

        # Character frequency analysis for the target language (English)
        if target_lang == "en":
            english_chars = sum(1 for char in content.lower() if 'a' <= char <= 'z')
            total_chars = len(content)
            english_ratio = english_chars / total_chars if total_chars > 0 else 0

            if english_ratio > 0.6:  # Adjust threshold as needed
                logging.info(f"Skipping {file_path} (appears to be English).")
                return True

        # Add more target language checks here if needed

        return False  # Not in target language

    except Exception as e:
        logging.warning(f"Could not read {file_path}, will attempt translation. Error: {e}")
        return False

# --- Main function to process files ---
def process_files(current_dir):
    """Processes files in the target directory, translating if not in the target language."""
    target_dir = os.path.join(current_dir, TARGET_DIR_NAME)

    if not os.path.exists(target_dir):
        logging.error(f"Target directory '{target_dir}' does not exist. Exiting.")
        return

    for root, dirs, files in os.walk(target_dir):
        for filename in files:
            file_path = os.path.join(root, filename)
            file_type = get_file_type(file_path)
            logging.debug(f"File: {file_path}, File type: {file_type}")

            if file_type == "unknown":
                logging.warning(f"Skipping unknown file type: {file_path}")
                continue

            try:
                logging.info(f"Processing file: {file_path}")

                if is_already_translated(file_path, TARGET_LANG):
                    continue

                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()

                if file_type == "markdown":
                    yaml_header = extract_yaml_header(content)
                    content_to_translate = extract_content_after_header(content)
                    translated_yaml = translate_yaml_values(yaml_header, TARGET_LANG, model)
                    translated_content = translate_text_with_gemini(content_to_translate, TARGET_LANG, file_type, model)
                    translated_text = translated_yaml + "\n\n" + translated_content if translated_content else translated_yaml
                else:
                    translated_text = translate_text_with_gemini(content, TARGET_LANG, file_type, model)

                if translated_text:
                    try:
                        with open(file_path, 'w', encoding='utf-8') as tf:
                            tf.write(translated_text)
                        logging.info(f"Translated {file_path} and saved.")
                    except Exception as e:
                        logging.error(f"Error writing to {file_path}: {e}", exc_info=True)
                else:
                    logging.error(f"Translation failed for {file_path}.")

            except Exception as e:
                logging.error(f"Error processing {file_path}: {e}", exc_info=True)
                continue

if __name__ == "__main__":
    current_directory = os.getcwd()
    logging.info("Starting translation process...")
    process_files(current_directory)
    logging.info("Translation process completed.")