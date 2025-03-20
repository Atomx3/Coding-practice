import os
from google.cloud import translate_v3 as translate
from google.oauth2 import service_account
from google.cloud import aiplatform
import logging

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def get_translation_info():
    """Outputs the API and model being used for translation."""

    # 检查环境变量
    PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
    CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")

    if not PROJECT_ID or not CREDENTIALS_PATH:
        return "Environment variables GOOGLE_CLOUD_PROJECT or GOOGLE_APPLICATION_CREDENTIALS not set."

    try:
        # 创建凭证对象
        credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
        
        # 尝试使用 Translation API v3
        try:
            client = translate.TranslationServiceClient(credentials=credentials)
            
            # 列出支持的位置
            locations = ["global", "us-central1", "europe-west4", "asia-northeast1"]
            available_models = []
            
            print("Available Translation API locations and models:")
            for location in locations:
                try:
                    parent = f"projects/{PROJECT_ID}/locations/{location}"
                    
                    # 获取支持的语言
                    supported_langs_request = translate.GetSupportedLanguagesRequest(parent=parent)
                    supported_langs = client.get_supported_languages(request=supported_langs_request)
                    print(f"\nLocation: {location}")
                    print(f"Supported languages count: {len(supported_langs.languages)}")
                    
                    # 尝试列出模型
                    try:
                        list_models_request = translate.ListModelsRequest(parent=parent)
                        list_models_response = client.list_models(request=list_models_request)
                        
                        models = list(list_models_response)
                        if models:
                            print(f"Available models in {location}:")
                            for model in models:
                                model_name = model.name.split('/')[-1]
                                available_models.append(f"{location}:{model_name}")
                                print(f"  - {model_name}")
                        else:
                            print(f"No custom models found in {location}")
                            
                        # 尝试检查内置模型
                        try:
                            # 测试翻译以检查默认模型
                            translate_request = translate.TranslateTextRequest(
                                parent=parent,
                                contents=["Hello world"],
                                mime_type="text/plain",
                                source_language_code="en",
                                target_language_code="fr"
                            )
                            translate_response = client.translate_text(request=translate_request)
                            if translate_response:
                                print(f"  - Default translation model is available in {location}")
                                available_models.append(f"{location}:default")
                        except Exception as e:
                            print(f"  - Error testing default model in {location}: {str(e)}")
                            
                    except Exception as e:
                        print(f"  - Error listing models in {location}: {str(e)}")
                        
                except Exception as e:
                    print(f"  - Error accessing location {location}: {str(e)}")
            
            # 尝试检查是否有 LLM 翻译模型
            llm_locations = ["us-central1"]
            for location in llm_locations:
                try:
                    parent = f"projects/{PROJECT_ID}/locations/{location}"
                    model_name = f"{parent}/models/general/translation-llm"
                    
                    # 尝试使用 LLM 模型进行简单翻译
                    translate_request = translate.TranslateTextRequest(
                        parent=parent,
                        contents=["Hello world"],
                        mime_type="text/plain",
                        source_language_code="en",
                        target_language_code="fr",
                        model=model_name
                    )
                    
                    try:
                        translate_response = client.translate_text(request=translate_request)
                        if translate_response:
                            print(f"\nLLM translation model is available: general/translation-llm in {location}")
                            available_models.append(f"{location}:general/translation-llm")
                    except Exception as e:
                        print(f"\nLLM translation model test failed: {str(e)}")
                except Exception as e:
                    print(f"\nError testing LLM model in {location}: {str(e)}")
            
            # 检查基础模型
            base_model_locations = ["us-central1", "global"]
            for location in base_model_locations:
                try:
                    parent = f"projects/{PROJECT_ID}/locations/{location}"
                    model_name = f"{parent}/models/general/base"
                    
                    # 尝试使用基础模型进行简单翻译
                    translate_request = translate.TranslateTextRequest(
                        parent=parent,
                        contents=["Hello world"],
                        mime_type="text/plain",
                        source_language_code="en",
                        target_language_code="fr",
                        model=model_name
                    )
                    
                    try:
                        translate_response = client.translate_text(request=translate_request)
                        if translate_response:
                            print(f"\nBase translation model is available: general/base in {location}")
                            available_models.append(f"{location}:general/base")
                    except Exception as e:
                        print(f"\nBase translation model test failed in {location}: {str(e)}")
                except Exception as e:
                    print(f"\nError testing base model in {location}: {str(e)}")
            
            # 汇总可用的模型
            if available_models:
                return f"Available Translation Models: {', '.join(available_models)}"
            else:
                return "No specific translation models found, but the Translation API is available."
                
        except Exception as e:
            logging.error(f"Translation API error: {str(e)}")
            
            # 如果 Translation API 出错，尝试使用 Vertex AI
            try:
                aiplatform.init(project=PROJECT_ID, credentials=credentials)
                
                # 列出可用的 Vertex AI 模型
                from google.cloud.aiplatform.models import Model
                
                models = Model.list()
                if models:
                    vertex_models = [model.display_name for model in models]
                    return f"API: Vertex AI, Available Models: {', '.join(vertex_models)}"
                else:
                    # 检查预定义的 Vertex AI 翻译端点
                    try:
                        endpoint = aiplatform.Endpoint(f'projects/{PROJECT_ID}/locations/us-central1/publishers/google/models/cloud-translate-text')
                        return f"API: Vertex AI Endpoint, Model: cloud-translate-text"
                    except:
                        return "Vertex AI is available but no translation models were found."
            except Exception as vertex_e:
                return f"Neither Translation API nor Vertex AI could be accessed: {str(e)}, {str(vertex_e)}"
    
    except Exception as e:
        return f"Error initializing services: {str(e)}"

# 调用函数并打印结果
if __name__ == "__main__":
    result = get_translation_info()
    print("\n" + "="*80)
    print("SUMMARY:")
    print(result)
    print("="*80)
