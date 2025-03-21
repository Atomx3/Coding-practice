# 简化版 Google Cloud Translation API 脚本，用于翻译目录中的文本文件
# 去掉文件格式markdown的预处理和prompt，直接将文本交给API翻译
# 通过chunk分块处理，避免超出API的长度限制   
# 检查文件是否已经翻译，如果是目标语言则跳过
import os
import logging
import time
import random
from google.cloud import translate_v3 as translate
from google.oauth2 import service_account
import mimetypes
from google.api_core.exceptions import ResourceExhausted
from ratelimit import limits, sleep_and_retry
from langdetect import detect, LangDetectException
import re

# --- 配置 ---
PROJECT_ID = os.environ.get("GOOGLE_CLOUD_PROJECT")
LOCATION = "us-central1"
CREDENTIALS_PATH = os.environ.get("GOOGLE_APPLICATION_CREDENTIALS")
MODEL_NAME = "general/translation-llm"
SOURCE_LANG = "zh-CN"
TARGET_LANG = "de"
TARGET_DIR_NAME = "de"
MIME_TYPE = "text/plain"
# API 调用频率限制
CALLS_PER_MINUTE = 15
ONE_MINUTE = 60
INITIAL_RETRY_DELAY = 2
MAX_RETRIES = 5
# 安全的分块大小，考虑到 API 额外开销
SAFE_CHUNK_SIZE = 600

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def preprocess_file_type(content):
    """
    简化的文件预处理函数，用于语言检测。
    移除常见的非语言元素，如代码、标记和格式符号。
    """
    # 1. 移除代码块 (```code```)
    content = re.sub(r'```[\s\S]*?```', '', content)
    
    # 2. 移除内联代码 (`code`)
    content = re.sub(r'`[^`]*?`', '', content)
    
    # 3. 移除HTML标签 (<tag>)
    content = re.sub(r'<[^>]*>', '', content)
    
    # 4. 移除YAML前置元数据 (---\nkey: value\n---)
    content = re.sub(r'^---[\s\S]*?---\n', '', content)
    
    # 5. 移除Markdown链接，保留链接文本 ([text](url))
    content = re.sub(r'\[([^\]]+)\]\([^)]+\)', r'\1', content)
    
    # 6. 移除URL
    content = re.sub(r'https?://\S+', '', content)
    
    # 7. 移除常见Markdown格式符号
    content = re.sub(r'[*_#>~|]', '', content)
    
    # 8. 移除多余空白并保留一些文本用于检测
    content = re.sub(r'\s+', ' ', content).strip()
    
    # 9. 提取一个合理大小的样本用于语言检测（避免处理过大的文本）
    # 从不同部分提取样本以增加准确性
    sample_size = min(500, len(content))
    if len(content) <= sample_size:
        return content
    
    # 从开头、中间和结尾各取一部分
    start = content[:sample_size//3]
    middle_start = max(0, len(content)//2 - sample_size//6)
    middle = content[middle_start:middle_start + sample_size//3]
    end_start = max(0, len(content) - sample_size//3)
    end = content[end_start:]
    
    return start + " " + middle + " " + end

def is_already_translated(file_path, target_lang):
    """检查文件是否已经翻译为目标语言 (第一步)"""
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
        
        # 如果文件为空，跳过翻译
        if not content.strip():
            logging.warning(f"文件为空: {file_path}，跳过翻译")
            return True
        
        # 预处理内容用于语言检测
        processed_content = preprocess_file_type(content)
        logging.info(f"预处理后的内容长度: {len(processed_content)} 字符")
        
        if not processed_content.strip():
            logging.warning(f"预处理后内容为空: {file_path}，跳过翻译")
            return True
        
        # 检测语言
        try:
            # 使用较长的样本进行检测
            sample = processed_content[:min(1000, len(processed_content))]
            detected_lang = detect(sample)
            logging.info(f"文件: {file_path}, 检测到语言: {detected_lang}, 目标语言: {target_lang}")
            
            # 标准化语言代码进行比较
            normalized_detected = detected_lang.lower()
            normalized_target = target_lang.lower()
            
            # 比较语言代码
            if normalized_detected == normalized_target:
                logging.info(f"文件已经是目标语言 {target_lang}，跳过翻译: {file_path}")
                return True
            else:
                logging.info(f"文件语言是 {detected_lang}，需要翻译为 {target_lang}: {file_path}")
                return False
                
        except LangDetectException as e:
            logging.warning(f"语言检测错误: {file_path}, {e}")
            return False  # 语言检测失败，默认需要翻译
            
    except Exception as e:
        logging.warning(f"检查文件语言时出错: {file_path}, {e}")
        return False  # 出错时默认需要翻译


# --- 环境验证 ---
REQUIRED_ENV_VARS = ["GOOGLE_CLOUD_PROJECT", "GOOGLE_APPLICATION_CREDENTIALS"]
missing_vars = [var for var in REQUIRED_ENV_VARS if os.environ.get(var) is None]
if missing_vars:
    logging.error(f"缺少必要的环境变量: {', '.join(missing_vars)}")
    exit(1)

# --- 初始化 Google Cloud 服务 ---
try:
    credentials = service_account.Credentials.from_service_account_file(CREDENTIALS_PATH)
    translate_client = translate.TranslationServiceClient(credentials=credentials)
    logging.info("成功初始化 Translation API 客户端。")
except Exception as e:
    logging.error(f"初始化服务时出错: {str(e)}")
    exit(1)

def get_file_type(file_path):
    """确定文件类型"""
    file_extension = os.path.splitext(file_path)[1].lower()
    if file_extension in [".md", ".txt", ".yaml"]:
        return "text"
    return "unknown"

@sleep_and_retry
@limits(calls=CALLS_PER_MINUTE, period=ONE_MINUTE)
def translate_chunk(text, target_lang, client):
    """翻译单个文本块"""
    if not text:
        return ""
    
    parent = f"projects/{PROJECT_ID}/locations/{LOCATION}"
    contents = [text]
    
    request = translate.TranslateTextRequest(
        parent=parent,
        contents=contents,
        mime_type=MIME_TYPE,
        source_language_code=SOURCE_LANG,
        target_language_code=target_lang,
        model=f"projects/{PROJECT_ID}/locations/{LOCATION}/models/{MODEL_NAME}"
    )

    for attempt in range(MAX_RETRIES):
        try:
            response = client.translate_text(request=request)
            return response.translations[0].translated_text
        except ResourceExhausted:
            delay = INITIAL_RETRY_DELAY * (2 ** attempt)
            logging.info(f"达到速率限制，等待 {delay} 秒后重试...")
            time.sleep(delay)
            continue
        except Exception as e:
            logging.error(f"翻译块时出错: {e}")
            time.sleep(1)  # 短暂暂停后重试
            continue
    
    logging.error(f"在 {MAX_RETRIES} 次尝试后翻译块失败")
    return None

def split_text(text, max_length=SAFE_CHUNK_SIZE):
    """优化的文本分块函数，尽量减少块数量"""
    if len(text) <= max_length:
        return [text]
    
    chunks = []
    paragraphs = text.split('\n\n')
    current_chunk = ""
    
    for paragraph in paragraphs:
        # 如果当前段落加上当前块不超过最大长度，则添加到当前块
        if len(current_chunk) + len(paragraph) + 2 <= max_length:
            if current_chunk:
                current_chunk += "\n\n" + paragraph
            else:
                current_chunk = paragraph
        # 如果段落本身超过最大长度，需要分割段落
        elif len(paragraph) > max_length:
            # 先添加当前块（如果有）
            if current_chunk:
                chunks.append(current_chunk)
                current_chunk = ""
            
            # 分割长段落（按句子）
            sentences = re.split(r'(?<=[.!?])\s+', paragraph)
            for sentence in sentences:
                if len(current_chunk) + len(sentence) + 1 <= max_length:
                    if current_chunk:
                        current_chunk += " " + sentence
                    else:
                        current_chunk = sentence
                else:
                    if current_chunk:
                        chunks.append(current_chunk)
                    current_chunk = sentence
        # 如果段落不适合当前块，开始新块
        else:
            chunks.append(current_chunk)
            current_chunk = paragraph
    
    # 添加最后一个块
    if current_chunk:
        chunks.append(current_chunk)
    
    return chunks


def translate_text(text, target_lang, client):
    """翻译文本，自动处理分块"""
    # 分割文本为安全大小的块
    chunks = split_text(text, SAFE_CHUNK_SIZE)
    logging.info(f"文本被分割为 {len(chunks)} 个块")
    
    # 记录每个块的大小，用于调试
    for i, chunk in enumerate(chunks):
        logging.info(f"块 {i+1}/{len(chunks)} 大小: {len(chunk)} 字符")
    
    translated_chunks = []
    for i, chunk in enumerate(chunks):
        logging.info(f"正在翻译块 {i+1}/{len(chunks)}")
        translated_chunk = translate_chunk(chunk, target_lang, client)
        if translated_chunk:
            translated_chunks.append(translated_chunk)
            logging.info(f"块 {i+1}/{len(chunks)} 翻译成功")
        else:
            logging.error(f"块 {i+1}/{len(chunks)} 翻译失败")
            return None  # 如果任何块翻译失败，返回 None
    
    # 合并翻译后的块
    result = "\n".join(translated_chunks)
    logging.info(f"所有块翻译完成，合并结果长度: {len(result)} 字符")
    return result


def process_files(current_dir, client):
    """处理目录中的文件进行翻译，严格按照检查->分块->翻译的顺序"""
    target_dir = os.path.join(current_dir, TARGET_DIR_NAME)
    if not os.path.exists(target_dir):
        logging.error(f"目标目录 '{target_dir}' 不存在。")
        return

    for root, _, files in os.walk(target_dir):
        for filename in files:
            file_path = os.path.join(root, filename)
            file_type = get_file_type(file_path)

            if file_type == "unknown":
                logging.warning(f"跳过未知文件类型: {file_path}")
                continue

            logging.info(f"处理文件: {file_path}")

            # 第一步: 明确检查文件是否已经翻译
            logging.info(f"步骤1: 检查文件是否已翻译: {file_path}")
            if is_already_translated(file_path, TARGET_LANG):
                logging.info(f"文件已经是目标语言 {TARGET_LANG}，跳过翻译: {file_path}")
                continue
            else:
                logging.info(f"文件需要翻译: {file_path}")

            try:
                # 读取文件内容
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read()
                
                # 第二步: 文本分块
                logging.info(f"步骤2: 对文件进行分块: {file_path}")
                chunks = split_text(content, SAFE_CHUNK_SIZE)
                logging.info(f"文件 {file_path} 被分割为 {len(chunks)} 个块")
                
                # 第三步: API翻译
                logging.info(f"步骤3: 发送到API进行翻译: {file_path}")
                translated_chunks = []
                for i, chunk in enumerate(chunks):
                    logging.info(f"翻译块 {i+1}/{len(chunks)}")
                    translated_chunk = translate_chunk(chunk, TARGET_LANG, client)
                    if translated_chunk:
                        translated_chunks.append(translated_chunk)
                        logging.info(f"块 {i+1}/{len(chunks)} 翻译成功")
                    else:
                        logging.error(f"块 {i+1}/{len(chunks)} 翻译失败")
                        break
                
                # 保存翻译结果
                if len(translated_chunks) == len(chunks):
                    logging.info(f"所有块翻译完成，合并并保存结果: {file_path}")
                    combined_translation = "\n".join(translated_chunks)
                    with open(file_path, 'w', encoding='utf-8') as tf:
                        tf.write(combined_translation)
                    logging.info(f"已翻译 {file_path} 并保存")
                else:
                    logging.error(f"翻译不完整: {file_path}，已翻译 {len(translated_chunks)}/{len(chunks)} 个块")
                    
            except Exception as e:
                logging.error(f"处理 {file_path} 时出错: {e}")
                import traceback
                logging.error(traceback.format_exc())


if __name__ == "__main__":
    current_directory = os.getcwd()
    logging.info("开始翻译过程...")
    process_files(current_directory, translate_client)
    logging.info("翻译过程完成。")
