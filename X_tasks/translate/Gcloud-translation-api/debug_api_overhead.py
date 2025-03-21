import logging
from google.cloud import translate_v3 as translate
from google.oauth2 import service_account
import os
import re
import time
import glob

# 设置详细日志
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

# 配置
PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = "us-central1"
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "general/translation-llm"
SOURCE_LANG = "zh-CN"
TARGET_LANG = "de"
TEST_DIR = "de"  # 测试文件目录

# 初始化客户端
credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
translate_client = translate.TranslationServiceClient(credentials=credentials)

def test_with_real_files():
    """使用实际文件测试API的额外开销"""
    # 获取测试目录中的所有文件
    files = glob.glob(f"{TEST_DIR}/**/*.*", recursive=True)
    
    if not files:
        logging.warning(f"在 {TEST_DIR} 目录中未找到任何文件")
        return
    
    logging.info(f"找到 {len(files)} 个测试文件")
    
    for file_path in files:
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                content = f.read()
            
            file_name = os.path.basename(file_path)
            content_length = len(content)
            logging.info(f"测试文件: {file_name}, 长度: {content_length} 字符")
            
            # 如果文件太大，我们需要截取一部分进行测试
            # 尝试不同长度的截取，以找到API的限制点
            test_lengths = [500, 600, 700, 800, 900, 1000]
            
            for length in test_lengths:
                if content_length < length:
                    # 如果文件内容不够长，使用全部内容
                    test_content = content
                    logging.info(f"文件内容长度 ({content_length}) 小于测试长度 ({length})，使用全部内容")
                else:
                    test_content = content[:length]
                    logging.info(f"截取前 {length} 个字符进行测试")
                
                try:
                    parent = f"projects/{PROJECT_ID}/locations/{LOCATION}"
                    contents = [test_content]
                    
                    request = translate.TranslateTextRequest(
                        parent=parent,
                        contents=contents,
                        mime_type="text/plain",
                        source_language_code=SOURCE_LANG,
                        target_language_code=TARGET_LANG,
                        model=f"projects/{PROJECT_ID}/locations/{LOCATION}/models/{MODEL_NAME}"
                    )
                    
                    response = translate_client.translate_text(request=request)
                    logging.info(f"长度 {len(test_content)} 字符的文本翻译成功")
                    
                except Exception as e:
                    error_msg = str(e)
                    logging.error(f"翻译错误: {error_msg}")
                    
                    if "Total text length:" in error_msg:
                        match = re.search(r"Total text length: (\d+)", error_msg)
                        if match:
                            reported_length = int(match.group(1))
                            actual_length = len(test_content)
                            overhead = reported_length - actual_length
                            
                            logging.info(f"API报告长度: {reported_length}, 实际文本长度: {actual_length}, 额外开销: {overhead} 字符")
                            
                            # 找到了额外开销，可以停止测试这个文件
                            break
                
                # 避免触发API速率限制
                time.sleep(2)
        
        except Exception as e:
            logging.error(f"处理文件 {file_path} 时出错: {e}")

def test_with_binary_search():
    """使用二分查找法确定API的额外开销"""
    # 基本测试文本 - 使用一个足够长的中文文本
    base_text = "这是一个测试文本，用于测试Google Cloud Translation API的额外开销。我们需要创建一个足够长的文本，以便触发API的长度限制。通过这种方式，我们可以确定API内部添加的额外字符数量。这对于优化我们的翻译程序非常重要，因为它可以帮助我们正确地分割文本，避免超出API的限制。" * 20
    
    # 二分查找的范围
    min_length = 400
    max_length = 1000
    
    while min_length <= max_length:
        mid_length = (min_length + max_length) // 2
        
        # 创建指定长度的文本
        test_text = base_text[:mid_length]
        actual_length = len(test_text)
        
        logging.info(f"二分查找 - 测试长度: {mid_length}, 实际文本长度: {actual_length} 字符")
        
        try:
            parent = f"projects/{PROJECT_ID}/locations/{LOCATION}"
            contents = [test_text]
            
            request = translate.TranslateTextRequest(
                parent=parent,
                contents=contents,
                mime_type="text/plain",
                source_language_code=SOURCE_LANG,
                target_language_code=TARGET_LANG,
                model=f"projects/{PROJECT_ID}/locations/{LOCATION}/models/{MODEL_NAME}"
            )
            
            response = translate_client.translate_text(request=request)
            logging.info(f"长度 {actual_length} 字符的文本翻译成功 - 尝试更长的文本")
            
            # 翻译成功，尝试更长的文本
            min_length = mid_length + 1
            
        except Exception as e:
            error_msg = str(e)
            
            if "Total text length:" in error_msg:
                match = re.search(r"Total text length: (\d+)", error_msg)
                if match:
                    reported_length = int(match.group(1))
                    overhead = reported_length - actual_length
                    
                    logging.info(f"API报告长度: {reported_length}, 实际文本长度: {actual_length}, 额外开销: {overhead} 字符")
                    
                    # 翻译失败，尝试更短的文本
                    max_length = mid_length - 1
            else:
                logging.error(f"翻译错误 (非长度相关): {error_msg}")
                # 如果是其他错误，也尝试更短的文本
                max_length = mid_length - 1
        
        # 避免触发API速率限制
        time.sleep(2)
    
    # 最终结果
    logging.info(f"\n===== 二分查找结果 =====")
    logging.info(f"最大可接受文本长度: 约 {min_length - 1} 字符")
    logging.info(f"估计额外开销: 约 {2000 - (min_length - 1)} 字符")

if __name__ == "__main__":
    # 检查测试目录是否存在
    if not os.path.exists(TEST_DIR):
        logging.error(f"测试目录 {TEST_DIR} 不存在，请先创建该目录并添加测试文件")
        exit(1)
    
    logging.info("开始测试实际文件...")
    test_with_real_files()
    
    logging.info("\n开始二分查找测试...")
    test_with_binary_search()
