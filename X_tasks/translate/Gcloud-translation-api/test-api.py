# Test Google Cloud Translation API - LLM, does it work?
# LLM model name is general/base ?
import os
from google.cloud import translate_v3 as translate
from google.oauth2 import service_account

PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = "global"
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "general/base"

def translate_text(text, target_lang):
    credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
    client = translate.TranslationServiceClient(credentials=credentials)
    parent = f"projects/{PROJECT_ID}/locations/{LOCATION}"
    response = client.translate_text(
        request={
            "parent": parent,
            "contents": [text],
            "mime_type": "text/plain",
            "source_language_code": "zh-CN",
            "target_language_code": target_lang,
            "model": f"projects/{PROJECT_ID}/locations/{LOCATION}/models/{MODEL_NAME}",
        }
    )
    return response.translations[0].translated_text

text = "你好，世界！"
target_lang = "en"
translated_text = translate_text(text, target_lang)
print(f"原文：{text}")
print(f"译文：{translated_text}")