# 测试翻译api调用是否正常；
# 查看api调用的翻译模型的版本，不同项目需求的适用模型也不同，必须精确匹配；

from google.cloud import translate_v2 as translate

def test_translation(api_key_path, project_id, text, target_language='en'):
    # 创建翻译客户端
    client = translate.Client.from_service_account_json(api_key_path)

    # 调用翻译 API 翻译文本
    result = client.translate(text, target_language=target_language, source_language='zh-CN')
    
    # 打印翻译结果
    print(f"Original Text: {text}")
    print(f"Translated Text: {result['translatedText']}")

if __name__ == "__main__":
    # 配置信息
    api_key_path = "/Users/atom.x/GitHub/Coolshell-in/test/venv/translate-441316-85865667e819.json"
    project_id = "translate-441316"
    
    # 要翻译的文本
    text = "你好，世界！伊娃，爸爸想你啦"
    
    # 目标语言
    target_language = "en"
    
    # 测试翻译 API 调用
    test_translation(api_key_path, project_id, text, target_language)
