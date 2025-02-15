# call gemini api, without parsing syntax of file format.
# translation quality is not stable.
import os  # For interacting with the operating system, like file paths.
import logging  # For logging events, useful for debugging and monitoring.
from google.cloud import aiplatform  # For accessing Vertex AI services.
from google.oauth2 import service_account  # For authenticating with Google Cloud using service account keys.
from vertexai.preview.generative_models import GenerativeModel, Part  # For using generative AI models.
from google.cloud import translate_v2 as translate  # For using the Google Cloud Translation API (for language detection).
import mimetypes # For detecting file types

# Configure logging
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# --- Configuration ---
PROJECT_ID = "translate-441316"  # Replace with your GCP project ID.
LOCATION = "europe-west3"       # Replace with your desired location.
CREDENTIALS_PATH = "/Users/atom.x/GitHub/Gcloud/.venv/translate-441316-0b7319d7ba9b.json"  # Replace with your service account key file path.
MODEL_NAME = "gemini-pro"       # Or "gemini-ultra". Choose the desired AI model.
PROJECT_ROOT_DIR = "/Users/atom.x/GitHub/Coolshell-in/translation-test3" # Project Root Directory.
SOURCE_DIR = "zh"  # Source language directory name.
SOURCE_LANG = "zh-TW"           # Source language code.
TARGET_DIRS = {
    "en": "en",  # Target language directory name, language tag.
    "de": "de",  # Target language directory name, language tag.
    "zhs":"zh-CN"  # Target language directory name, language tag.
}
# ---- End Configuration ----

# Initialize language detection cache
language_cache = {}  # To store detected language to avoid repeated API calls.

# Load credentials
try:
    credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
    logging.info("Service account credentials loaded successfully.")
except Exception as e:
    logging.error(f"Error loading service account credentials: {e}")
    exit()

# Initialize Vertex AI with credentials
aiplatform.init(project=PROJECT_ID, location=LOCATION, credentials=credentials)
logging.info(f"Vertex AI initialized with project: {PROJECT_ID}, location: {LOCATION}")

# Initialize Gemini Model
ai_model = GenerativeModel(model_name=MODEL_NAME)
logging.info(f"Using model: {MODEL_NAME}")

# Initialize Translate API client
translate_client = translate.Client(credentials=credentials)


def get_file_type(file_path):
    """Gets the MIME type and a simplified file type description."""
    mime_type, _ = mimetypes.guess_type(file_path)
    if mime_type:
        if mime_type == "text/markdown":
            return "markdown"
        elif mime_type == "text/x-yaml":
            return "yaml"
        elif mime_type.startswith("text/"):  # Generic text type
            return "text"
        else:
            return "other" # Or handle other specific types as needed
    return "unknown"


def translate_text_with_gemini(text, target_language, source_language=SOURCE_LANG, file_type="text"):
    """Translates text using the specified Gemini model.

    Args:
        text (str): The text to be translated.
        target_language (str): The target language code (BCP 47).
        source_language (str, optional): The source language code (BCP 47). Defaults to SOURCE_LANG.

    Returns:
        str: The translated text, or None if translation fails.
    """
    try:
        if not text:
            logging.warning("Text to translate is empty. Skipping translation.")
            return ""

        logging.info(f"Translating from {source_language} to {target_language}: {text[:50]}...")

        # Modified prompt to restrict AI's behavior
        prompt = f"""Translate the following {file_type} format document from {source_language} to {target_language} as if you were translating a document in a Gemini chatbot conversation.  Adhere to these specific instructions:

        *   Preserve all original formatting meticulously. Pay special attention to formatting elements such as markdown, YAML, XML/HTML, and JSON etc.
        *   Do not add any additional explanations, context, examples, providing only the translation text relevant to the source content.
        *   Maintain the original tone and style of the text to the best of your ability.
        *   Pay attention to cultural nuances and avoid literal translations where appropriate.
        *   Maintain consistent translation standards and conventions throughout all files. For example, 
        When handling named entities (Bible, Famous Quotations, Person Names, Places, Book Titles, Movie Titles, Chinese 成语典故 (Idiomatic Expression with Historical Background) and 歇后语 (Punning Riddle or Two-Part Allegorical Saying) ), please maintain both the original text and the translated one.
        enclose the original text in square brackets followed by the translation, like this: " [original_text]translation text". For example: "[狐假虎威] The fox exploits the tiger's might ".

        User: Please translate the following document:
        """

        contents=[
            Part.from_text(prompt),
            Part.from_text(text)
        ]

        response = ai_model.generate_content(
            contents,
            generation_config={
                "candidate_count": 1,
                "max_output_tokens": 2048,
                "temperature": 0.2
            }
        )

        if response.text:
            logging.info(f"Translation successful: {response.text[:50]}...")
            return response.text
        else:
            logging.warning("Translation failed: No text in response.")
            return None

    except Exception as e:
        logging.error(f"An error occurred during translation: {e}")
        return None


def detect_language(text):
    """Detects the language of the given text using Translate API, and uses cache.

    Args:
        text (str): The text to be analyzed.

    Returns:
         str: The detected language code, or None if detection fails.
    """
    if text in language_cache:
        return language_cache[text]
    try:
        result = translate_client.detect_language(text)
        language_code = result['language']
        language_cache[text] = language_code
        return language_code
    except Exception as e:
            logging.error(f"Error detecting language: {e}")
            return None


def process_file(source_file_path, target_dir_path, target_language, source_language=SOURCE_LANG):
    """Processes a single source file and translates it, overwriting existing files."""

    relative_path = os.path.relpath(source_file_path, os.path.join(PROJECT_ROOT_DIR, SOURCE_DIR))
    target_file_path = os.path.join(target_dir_path, relative_path)

    logging.info(f"Processing file: {source_file_path} to {target_file_path} (Target Language: {target_language})")

    # Ensure target directory exists
    os.makedirs(os.path.dirname(target_file_path), exist_ok=True)

    try:
        with open(source_file_path, 'r', encoding='utf-8') as source_file:
            source_text = source_file.read()

        file_type = get_file_type(source_file_path)
        translated_text = translate_text_with_gemini(source_text, target_language, source_language, file_type)

        if translated_text:
            with open(target_file_path, 'w', encoding='utf-8') as target_file:
                target_file.write(translated_text)
                logging.info(f"Translated and saved file: {target_file_path}")
        else:
            logging.warning(f"Translation failed for file: {source_file_path}")

    except FileNotFoundError:
        logging.error(f"Source file not found: {source_file_path}")
    except Exception as e:
        logging.error(f"An error occurred during file processing: {e}")


def process_directory(project_root_dir, source_dir_name, target_dirs,source_language=SOURCE_LANG):
    """Processes the source directory recursively and translates all files to different target languages.

        Args:
            project_root_dir (str): The project root directory.
            source_dir_name (str): The source directory name.
            target_dirs (dict): A dictionary of target language directories.
            source_language (str, optional): The source language code (BCP 47). Defaults to SOURCE_LANG.

    """
    source_dir = os.path.join(project_root_dir, source_dir_name)
    for root, _, files in os.walk(source_dir):
      for file in files:
          source_file_path = os.path.join(root, file)
          for target_dir, target_lang in target_dirs.items():
              target_dir_path = os.path.join(project_root_dir, target_dir)
              process_file(source_file_path, target_dir_path, target_lang, source_language)

# Main entry
if __name__ == "__main__":
    language_cache = {} # Clear language cache at the beginning of each run
    logging.info("Starting translation process...")
    process_directory(PROJECT_ROOT_DIR, SOURCE_DIR, TARGET_DIRS,SOURCE_LANG)
    logging.info("Translation process finished.")
