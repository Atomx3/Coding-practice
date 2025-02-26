import os
import logging
import re
import traceback
import time
import random
from google.cloud import aiplatform
from google.oauth2 import service_account
from vertexai.preview.generative_models import GenerativeModel, Part, SafetySetting
import mimetypes
from google.api_core.exceptions import ResourceExhausted

# Configuration
PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = os.environ.get("GOOGLE_CLOUD_REGION", "europe-west3")
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "gemini-1.5-pro-001"
SOURCE_LANG = "zh-CN"
TARGET_LANG = "en"
TARGET_DIR_NAME = "en"
MAX_OUTPUT_TOKENS = 8192
TEMPERATURE = 0.3
TOP_P = 0.9

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

# Check required environment variables
REQUIRED_ENV_VARS = ["GOOGLE_CLOUD_PROJECT", "GOOGLE_APPLICATION_CREDENTIALS"]
missing_vars = [var for var in REQUIRED_ENV_VARS if os.environ.get(var) is None]
if missing_vars:
    logging.error(f"Missing required environment variables: {', '.join(missing_vars)}")
    exit(1)

# Initialize Google Cloud services
try:
    credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
    aiplatform.init(project=PROJECT_ID, location=LOCATION, credentials=credentials)
    model = GenerativeModel(MODEL_NAME)
    logging.info(f"Successfully initialized {MODEL_NAME} model.")
except Exception as e:
    logging.error(f"Error initializing services: {str(e)}")
    exit(1)

# Helper functions
def get_file_type(file_path):
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
    header_start = text.find("---")
    if header_start == -1:
        return ""
    header_end = text.find("---", header_start + 1)
    if header_end == -1:
        return text
    return text[header_start:header_end + 3]

def extract_content_after_header(text):
    header_end = text.find("---", text.find("---") + 1)
    if header_end == -1:
        return text
    return text[header_end + 3:]

def translate_yaml_values(yaml_header, target_lang, model):
    lines = yaml_header.splitlines()
    translated_lines = []
    for line in lines:
        if ":" in line:
            key, value = line.split(":", 1)
            key = key.strip()
            value = value.strip()
            if key in ["title", "date", "description", "categories", "tags"]:
                translated_lines.append(line)
                continue
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
            translated_lines.append(line)
    return "\n".join(translated_lines)

def translate_text_with_gemini(text, target_lang, file_type="text", model=model):
    if not text:
        return ""
    
    prompt = f"""您是一位专业翻译。请将以下内容从{SOURCE_LANG}翻译成{target_lang}。

关键要求：
- 这是{file_type}文件。严格保留所有原始格式、语法标记和结构；
- 对于Markdown格式文件，保持YAML格式的头部信息中的英文关键字（如title, date, description, categories, tags等），其后的值要翻译；
- 对于命名实体，即文中引用的组织名称、名人、名言、普通人名、地名、图书（圣经、经典）、电影名称、中文成语典故、歇後語和寓言短语等特定的专有名词或名称，应该保留一份原文的源语言、汉语拼音或罗马拼音，同时一份对应翻译的目标语言，使用格式：\"[原文 汉语拼音] 译文\"；
- 保留文件中的链接，包括带有https的外链，以及内链，也就是内部的文件链接，通常格式例如this-is-an-inner-file-link.md；
- 直接提供翻译，无需额外解释、上下文或示例，在保持文化适当性的同时维持原有语气和风格；
"""
    
    max_retries = 5
    initial_delay = 1
    
    for attempt in range(max_retries):
        try:
            response = model.generate_content(
                [Part.from_text(prompt), Part.from_text(text)],
                generation_config={
                    "max_output_tokens": MAX_OUTPUT_TOKENS,
                    "temperature": TEMPERATURE,
                    "top_p": TOP_P
                },
                safety_settings=[
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_HATE_SPEECH, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_DANGEROUS_CONTENT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_SEXUALLY_EXPLICIT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE),
                    SafetySetting(category=SafetySetting.HarmCategory.HARM_CATEGORY_HARASSMENT, threshold=SafetySetting.HarmBlockThreshold.BLOCK_MEDIUM_AND_ABOVE)
                ]
            )
            
            if not response or not response.text:
                logging.warning(f"Received empty response from Gemini. Attempt {attempt + 1}/{max_retries}")
                if attempt == max_retries - 1:
                    return None
                continue
            
            return response.text
        
        except ResourceExhausted:
            logging.warning(f"Rate limit exceeded. Attempt {attempt + 1}/{max_retries}. Retrying in {initial_delay} seconds...")
            time.sleep(initial_delay + random.uniform(0, 1))
            initial_delay *= 2
        except Exception as e:
            logging.error(f"Translation error: {e}")
            logging.error(traceback.format_exc())
            return None
    
    logging.error(f"Translation failed after {max_retries} attempts.")
    return None

def is_already_translated(file_path, target_lang):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        if target_lang == "en":
            english_chars = sum(1 for char in content.lower() if 'a' <= char <= 'z')
            total_chars = len(content)
            english_ratio = english_chars / total_chars if total_chars > 0 else 0
            
            if english_ratio > 0.6:
                logging.info(f"Skipping {file_path} (appears to be English).")
                return True
        
        return False
    
    except Exception as e:
        logging.warning(f"Could not read {file_path}, will attempt translation. Error: {str(e)}")
        return False

def process_files(current_dir):
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
                
                if translated_text is not None:
                    try:
                        with open(file_path, 'w', encoding='utf-8') as tf:
                            tf.write(translated_text)
                        logging.info(f"Translated {file_path} and saved.")
                    except Exception as e:
                        logging.error(f"Error writing to {file_path}: {str(e)}", exc_info=True)
                else:
                    logging.error(f"Translation failed for {file_path}.")
            
            except Exception as e:
                logging.error(f"Error processing {file_path}: {str(e)}", exc_info=True)
                continue

if __name__ == "__main__":
    current_directory = os.getcwd()
    logging.info("Starting translation process...")
    process_files(current_directory)
    logging.info("Translation process completed.")
