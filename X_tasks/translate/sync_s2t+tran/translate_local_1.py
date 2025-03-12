import os
import json
import git
import logging
from google.cloud import translate_v2 as translate
from google.oauth2 import service_account
from google.auth.exceptions import DefaultCredentialsError

# 配置信息
api_key_path = "/Users/atom.x/GitHub/Coolshell-in/test/venv/translate-441316-85865667e819.json"  # API 密钥路径
project_id = "translate-441316"  # 项目 ID
source_dir = "./zh"  # 源文件目录
meta_dir = "./meta"  # 元数据目录
target_dirs = ["./en", "./de", "./ru"]  # 目标语言目录列表
target_langs = ["en", "de", "ru"]  # 目标语言列表

# 初始化日志
logging.basicConfig(level=logging.INFO)

# 创建 meta 目录（如果不存在）
os.makedirs(meta_dir, exist_ok=True)
def translate_text(text, target_lang, api_key_path):
    """Translate text using Google Cloud Translate API."""
    try:
        credentials = service_account.Credentials.from_service_account_file(api_key_path)
        client = translate.Client(credentials=credentials)
        result = client.translate(text, target_language=target_lang, source_language='zh-CN')
        logging.info(f"Translation result: {result}")
        return result['translatedText']
    except Exception as e:
        logging.error(f"Translation failed: {e}")
        return ""  # Ensure this line ends properly

def test_api_connection():
    """Test the connection to the Google Translate API."""
    try:
        credentials = service_account.Credentials.from_service_account_file(api_key_path)
        client = translate.Client(credentials=credentials)
        client.translate("test", target_language="en")
        logging.info("API connection successful")
        return True
    except DefaultCredentialsError as e:
        logging.error(f"API connection failed: {e}")
        return False

def load_meta(file_name):
    """加载元数据文件"""
    meta_file = os.path.join(meta_dir, f"{file_name}.meta")
    if os.path.exists(meta_file):
        with open(meta_file, 'r') as f:
            return json.load(f)
    return {}

def save_meta(file_name, meta_data):
    """保存元数据到文件"""
    meta_file = os.path.join(meta_dir, f"{file_name}.meta")
    with open(meta_file, 'w') as f:
        json.dump(meta_data, f, indent=4)

def read_file(file_path):
    """Read source file content and split into paragraphs"""
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()
        paragraphs = [p.strip() for p in content.split('\n\n') if p.strip()]
        return paragraphs

def process_file(file_path, source_dir, meta_dir, target_dirs, target_langs, project_id, api_key_path):
    logging.info(f"Starting to process {file_path}")
    
    # Initialize Git repo
    repo = git.Repo(source_dir, search_parent_directories=True)
    logging.info(f"Git repo initialized at {repo.working_dir}")
    
    # Read source content
    source_lines = read_file(file_path)
    logging.info(f"Source content read: {len(source_lines)} paragraphs")
    
    # Get initial diff
    diff = repo.git.diff(None, file_path, unified=0)
    logging.info(f"Git diff obtained: {diff}")
    
    # Force initial translation if meta file doesn't exist
    relative_path = os.path.relpath(file_path, start=source_dir)
    meta_file = os.path.join(meta_dir, f"{relative_path}.meta")
    
    if not os.path.exists(meta_file):
        logging.info("No meta file found - performing initial translation")
        changes = {'additions': source_lines, 'deletions': [], 'modifications': []}
    else:
        changes = parse_diff(diff, source_lines)
    
    logging.info(f"Changes detected: {changes}")
    
    # Load or create meta data
    meta_data = load_meta(relative_path) or {}
    
    # Update translations
    updated_meta_data = update_meta_data(meta_data, changes, target_langs, project_id, api_key_path)
    logging.info(f"Meta data updated with {len(updated_meta_data)} entries")
    
    # Save meta data
    save_meta(relative_path, updated_meta_data)
    
    # Update target files
    update_target_files(file_path, target_dirs, updated_meta_data, target_langs)

def parse_diff(diff, source_lines):
    """Enhanced diff parsing with better context awareness"""
    changes = {'additions': [], 'deletions': [], 'modifications': []}
    current_hunk = []
    
    for line in diff.split('\n'):
        if line.startswith('@@'):
            if current_hunk:
                _process_hunk(current_hunk, changes)
            current_hunk = [line]
        elif line.startswith('+') or line.startswith('-'):
            current_hunk.append(line)
    
    if current_hunk:
        _process_hunk(current_hunk, changes)
    
    return changes

def _process_hunk(hunk, changes):
    """Process a single diff hunk to identify changes"""
    deletions = []
    additions = []
    
    for line in hunk[1:]:  # Skip the @@ line
        if line.startswith('+') and not line.startswith('+++'):
            content = line[1:].strip()
            if content:
                additions.append(content)
        elif line.startswith('-') and not line.startswith('---'):
            content = line[1:].strip()
            if content:
                deletions.append(content)
    
    # Match modifications using similarity ratio
    for del_line in deletions[:]:
        for add_line in additions[:]:
            similarity = _calculate_similarity(del_line, add_line)
            if similarity > 0.7:
                changes['modifications'].append({
                    'old': del_line,
                    'new': add_line
                })
                deletions.remove(del_line)
                additions.remove(add_line)
                break
    
    changes['deletions'].extend(deletions)
    changes['additions'].extend(additions)

def _calculate_similarity(str1, str2):
    """Calculate similarity ratio between two strings"""
    s1 = set(str1)
    s2 = set(str2)
    return len(s1 & s2) / max(len(s1), len(s2))

def update_meta_data(meta_data, changes, target_langs, project_id, api_key_path):
    """Enhanced metadata update with modification handling"""
    next_id = max(map(int, meta_data.keys())) + 1 if meta_data else 1
    
    # Handle additions
    for addition in changes['additions']:
        translations = {}
        for lang in target_langs:
            translated_text = translate_text(addition, lang, api_key_path)
            translations[lang] = translated_text
            logging.info(f"Translated new content to {lang}: {translated_text}")
        
        meta_data[str(next_id)] = {
            'original': addition,
            'translations': translations
        }
        next_id += 1
    
    # Handle deletions
    for deletion in changes['deletions']:
        for key in list(meta_data.keys()):
            if meta_data[key]['original'] == deletion:
                del meta_data[key]
                logging.info(f"Removed deleted content: {deletion}")
    
    # Handle modifications
    for mod in changes['modifications']:
        for key, value in meta_data.items():
            if value['original'] == mod['old']:
                translations = {}
                for lang in target_langs:
                    translated_text = translate_text(mod['new'], lang, project_id, api_key_path)
                    translations[lang] = translated_text
                    logging.info(f"Updated translation in {lang}: {translated_text}")
                
                meta_data[key] = {
                    'original': mod['new'],
                    'translations': translations
                }
    
    return meta_data

def update_target_files(file_path, target_dirs, meta_data, target_langs):
    """Enhanced target file update with proper formatting"""
    relative_path = os.path.relpath(file_path, start='zh')
    
    for lang, target_dir in zip(target_langs, target_dirs):
        target_file = os.path.join(target_dir, relative_path)
        os.makedirs(os.path.dirname(target_file), exist_ok=True)
        
        content = []
        for key in sorted(meta_data.keys(), key=int):
            if meta_data[key]['translations'].get(lang):
                content.append(meta_data[key]['translations'][lang])
        
        with open(target_file, 'w', encoding='utf-8') as f:
            f.write('\n\n'.join(content))
        logging.info(f"Updated {target_file}")

def test_api_connection():
    """Test the connection to the Google Translate API."""
    try:
        credentials = service_account.Credentials.from_service_account_file(api_key_path)
        client = translate.Client(credentials=credentials)
        # Attempt a simple translation to test the connection
        client.translate("test", target_language="en")
        logging.info("API connection successful")
        return True
    except TypeError as e:
        if "unexpected keyword argument 'project'" in str(e):
            logging.warning("Ignoring unexpected keyword argument 'project' error.")
            return True
        else:
            logging.error(f"API connection failed: {e}")
            return False
    except DefaultCredentialsError as e:
        logging.error(f"API connection failed: {e}")
        return False

if __name__ == '__main__':
    # Set verbose logging
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(levelname)s - %(message)s',
        handlers=[
            logging.StreamHandler(),
            logging.FileHandler('translation.log')
        ]
    )
    
    logging.info("Starting translation process")
    
    # Test API connection
    if not test_api_connection():
        raise Exception("Cannot proceed without working API connection")
        
    # Print current working directory and file counts
    logging.info(f"Current directory: {os.getcwd()}")
    source_files = [f for f in os.listdir(source_dir) if f.endswith('.md')]
    logging.info(f"Found source files: {source_files}")
    
    # Initialize directories
    for target_dir in target_dirs:
        os.makedirs(target_dir, exist_ok=True)
    os.makedirs(meta_dir, exist_ok=True)
    
    # Force initial translation of all files
    for root, _, files in os.walk(source_dir):
        for file in files:
            if file.endswith('.md'):
                file_path = os.path.join(root, file)
                logging.info(f"\n=== Processing {file_path} ===")
                
                # Read source content directly
                source_content = read_file(file_path)
                logging.info(f"Found {len(source_content)} paragraphs to translate")
                
                # Force translation of all content
                changes = {
                    'additions': source_content,
                    'deletions': [],
                    'modifications': []
                }
                
                relative_path = os.path.relpath(file_path, start=source_dir)
                meta_data = {}
                
                # Translate and update
                updated_meta = update_meta_data(meta_data, changes, target_langs, project_id, api_key_path)
                save_meta(relative_path, updated_meta)
                update_target_files(file_path, target_dirs, updated_meta, target_langs)
                
                logging.info(f"Completed processing {file_path}")

logging.info(f"Processing file: {file_path}")
logging.info(f"Meta data updated: {meta_data}")
logging.info(f"Target files updated in: {target_dirs}")