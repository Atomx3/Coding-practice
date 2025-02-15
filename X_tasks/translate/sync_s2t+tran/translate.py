# 翻译本地文件，并使用git进行版本控制，跟踪源文件和目录结构的变化，同步更新到目标语言文件。
import os
import hashlib
import openai
from git import Repo
from typing import List, Dict

# 设置 OpenAI API 密钥
openai.api_key = os.getenv("OPENAI_API_KEY")

# 基础配置
SOURCE_DIR = 'zhs'
TARGET_LANGS = ['en', 'de', 'ru']
META_DIR = 'meta'
REPO_PATH = '.'  # Git 仓库路径


def hash_paragraph(paragraph: str) -> str:
    """为每段生成唯一标号（哈希值）"""
    return hashlib.md5(paragraph.encode('utf-8')).hexdigest()


def parse_file(filepath: str) -> Dict[str, str]:
    """解析文件并生成段落哈希映射"""
    with open(filepath, 'r', encoding='utf-8') as f:
        paragraphs = f.read().split('\n\n')
    return {hash_paragraph(p): p for p in paragraphs if p.strip()}


def detect_changes(filepath: str) -> Dict[str, List[str]]:
    """检测源文件段落的新增、删除和修改，返回变化的段落哈希值"""
    # 加载旧的元数据
    meta_path = os.path.join(META_DIR, os.path.basename(filepath) + '.meta')
    if os.path.exists(meta_path):
        with open(meta_path, 'r', encoding='utf-8') as f:
            old_data = f.read().splitlines()
        old_paragraphs = {line.split('|')[0]: line.split('|')[1] for line in old_data}
    else:
        old_paragraphs = {}

    # 加载新的段落数据
    new_paragraphs = parse_file(filepath)

    # 检测段落变化
    changes = {'added': [], 'deleted': [], 'modified': []}
    for h in new_paragraphs:
        if h not in old_paragraphs:
            changes['added'].append(h)
        elif new_paragraphs[h] != old_paragraphs[h]:
            changes['modified'].append(h)

    for h in old_paragraphs:
        if h not in new_paragraphs:
            changes['deleted'].append(h)

    # 更新元数据文件
    with open(meta_path, 'w', encoding='utf-8') as f:
        for h, p in new_paragraphs.items():
            f.write(f"{h}|{p}\n")

    return changes


def translate_paragraph(paragraph: str, target_language: str) -> str:
    """调用 OpenAI API 将段落翻译为目标语言"""
    response = openai.ChatCompletion.create(
        model="gpt-4",
        messages=[
            {"role": "system", "content": f"Translate the following Chinese text to {target_language}."},
            {"role": "user", "content": paragraph}
        ],
        temperature=0.2
    )
    return response.choices[0].message['content'].strip()


def update_target_file(filepath: str, changes: Dict[str, List[str]], target_lang: str):
    """根据变化更新目标语言文件"""
    # 加载目标文件
    target_filepath = filepath.replace(SOURCE_DIR, target_lang)
    if os.path.exists(target_filepath):
        with open(target_filepath, 'r', encoding='utf-8') as f:
            paragraphs = f.read().split('\n\n')
        target_paragraphs = parse_file(target_filepath)
    else:
        paragraphs = []
        target_paragraphs = {}

    # 更新目标文件的内容
    with open(target_filepath, 'w', encoding='utf-8') as f:
        for h, p in parse_file(filepath).items():
            if h in changes['deleted']:
                continue
            elif h in changes['added'] or h in changes['modified']:
                translated_paragraph = translate_paragraph(p, target_lang)
                f.write(f"{translated_paragraph}\n\n")
            else:
                f.write(f"{target_paragraphs.get(h, '')}\n\n")


def main():
    """主函数：检测 zhs 目录中的文件变化并翻译更新"""
    repo = Repo(REPO_PATH)
    changed_files = [item.a_path for item in repo.index.diff(None) if item.a_path.startswith(SOURCE_DIR)]

    for file in changed_files:
        changes = detect_changes(file)
        if not any(changes.values()):
            continue  # 如果没有新增、删除或修改的段落，跳过

        for lang in TARGET_LANGS:
            update_target_file(file, changes, lang)


if __name__ == "__main__":
    main()