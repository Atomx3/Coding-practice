import os
import json
import shutil
from markdown_processor import parse_content_into_blocks, generate_block_id

def ensure_meta_dir_exists(meta_dir):
    os.makedirs(meta_dir, exist_ok=True)

def detect_file_format(source_file_path):
    _, ext = os.path.splitext(source_file_path)
    return ext.lower()

class MetaDataManager:
    def __init__(self, meta_dir):
        self.meta_dir = meta_dir
        ensure_meta_dir_exists(meta_dir)
        
    def sync_meta_for_file(self, source_file, operation_type, is_target=False):
        meta_file = self._get_meta_path(source_file)
        
        if operation_type == 'delete':
            if os.path.exists(meta_file):
                os.remove(meta_file)
            return
            
        current_blocks = parse_content_into_blocks(self._read_file(source_file), preserve_whitespace=True)
        
        if is_target:
            # Load existing meta to preserve target-specific content
            existing_meta = self._load_meta(meta_file) if os.path.exists(meta_file) else None
            if existing_meta:
                self._merge_target_changes(current_blocks, existing_meta['blocks'])
                
        meta_data = {
            'source_file': source_file,
            'blocks': [{
                'id': generate_block_id(block['content']),
                'content': block['content'],
                'whitespace': block['whitespace_before'],
                'modified_in_target': block.get('modified_in_target', False)
            } for block in current_blocks]
        }
        
        self._save_meta(meta_file, meta_data)
        
    def _merge_target_changes(self, current_blocks, meta_blocks):
        # Map existing blocks by their IDs
        meta_block_map = {block['id']: block for block in meta_blocks}
        
        for block in current_blocks:
            block_id = generate_block_id(block['content'])
            if block_id in meta_block_map:
                block['modified_in_target'] = meta_block_map[block_id].get('modified_in_target', False)

    def _get_meta_path(self, source_file):
        rel_path = os.path.relpath(source_file)
        return os.path.join(self.meta_dir, f"{rel_path}.meta")

    def _read_file(self, file_path):
        with open(file_path, 'r', encoding='utf-8') as f:
            return f.read()

    def _save_meta(self, meta_file, meta_data):
        os.makedirs(os.path.dirname(meta_file), exist_ok=True)
        with open(meta_file, 'w', encoding='utf-8') as f:
            json.dump(meta_data, f, indent=4, ensure_ascii=False)

    def _load_meta(self, meta_file):
        with open(meta_file, 'r', encoding='utf-8') as f:
            return json.load(f)

    def handle_file_move(self, old_path, new_path):
        """Handle the move of a source file by updating its meta data path."""
        old_meta_path = self._get_meta_path(old_path)
        new_meta_path = self._get_meta_path(new_path)
        
        if os.path.exists(old_meta_path):
            os.makedirs(os.path.dirname(new_meta_path), exist_ok=True)
            shutil.move(old_meta_path, new_meta_path)
def cleanup_meta_directory(source_dir, meta_dir):
    """Remove meta files if the corresponding source file is deleted."""
    # Get all existing source files
    existing_source_files = set()
    for root, _, files in os.walk(source_dir):
        rel_path = os.path.relpath(root, source_dir)
        for file in files:
            if file.endswith('.md'):
                existing_source_files.add(os.path.join(rel_path, file))

    # Clean meta directory based on source files
    for root, _, files in os.walk(meta_dir):
        rel_path = os.path.relpath(root, meta_dir)
        for file in files:
            if file.endswith('.meta'):
                source_file = os.path.join(rel_path, file[:-5])
                if source_file not in existing_source_files:  # Check only source files
                    meta_file_path = os.path.join(root, file)
                    os.remove(meta_file_path)

    # Clean empty directories in meta
    for root, dirs, _ in os.walk(meta_dir, topdown=False):
        for dir_name in dirs:
            dir_path = os.path.join(root, dir_name)
            if not os.listdir(dir_path):
                os.rmdir(dir_path)

def generate_metadata_for_all_files(source_dir, target_dirs, meta_dir):
    """Generate metadata for all source files."""
    for root, _, files in os.walk(source_dir):
        for file in files:
            if file.endswith('.md'):
                source_file_path = os.path.join(root, file)
                generate_and_save_metadata(source_file_path, meta_dir, source_dir, target_dirs)

def MetaManager(source_dir, target_dirs, meta_dir):
    """Initialize and manage all metadata operations."""
    cleanup_meta_directory(source_dir, meta_dir)
    generate_metadata_for_all_files(source_dir, target_dirs, meta_dir)
    # Add other metadata management tasks here if needed

def generate_and_save_metadata(source_file_path, meta_dir, source_dir, target_dirs):
    metadata = {
        'source_file_path': source_file_path,
        'blocks': []
    }
    
    with open(source_file_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    blocks = parse_content_into_blocks(content)
    
    for block in blocks:
        # Generate short 5-character hash as block ID
        block_id = generate_block_id(block['content'])[:5]
        content_map = {}
        
        # Store only first 5 characters of content for each directory
        for dir_path in [source_dir] + target_dirs:
            dir_name = f'./{os.path.basename(dir_path)}/'
            content_map[dir_name] = block['content'][:5]
        
        metadata['blocks'].append({
            'id': block_id,
            'content': content_map
        })
    
    meta_path = os.path.join(meta_dir, os.path.relpath(source_file_path, source_dir) + '.meta')
    os.makedirs(os.path.dirname(meta_path), exist_ok=True)
    
    with open(meta_path, 'w', encoding='utf-8') as f:
        json.dump(metadata, f, indent=4, ensure_ascii=False)