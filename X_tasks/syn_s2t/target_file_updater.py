import os
import shutil
from markdown_processor import parse_content_into_blocks, generate_block_id

class TargetUpdater:
    def __init__(self, source_dir, target_dirs, meta_dir):
        self.source_dir = source_dir
        self.target_dirs = target_dirs
        self.meta_dir = meta_dir

    # Other methods...
        
    def sync_files(self, logger):
        try:
            source_files = self._handle_new_modified_files(logger)
            self._handle_deleted_files(logger, source_files)
            return True, []
        except Exception as e:
            return False, [str(e)]

    def _handle_new_modified_files(self, logger):
        source_files = set()
        for root, _, files in os.walk(self.source_dir):
            for file in files:
                if file.endswith('.md'):
                    rel_path = os.path.relpath(os.path.join(root, file), self.source_dir)
                    source_files.add(rel_path)
                    source_file = os.path.join(root, file)
                    
                    # Process target files
                    for target_dir in self.target_dirs:
                        target_path = os.path.join(target_dir, rel_path)
                        if os.path.exists(target_path):
                            self._sync_target_file(source_file, target_path, logger)
                        else:
                            # New file - copy directly
                            os.makedirs(os.path.dirname(target_path), exist_ok=True)
                            shutil.copy2(source_file, target_path)
                            
        return source_files
        
    def _sync_target_file(self, source_file, target_path, logger):
        source_blocks = parse_content_into_blocks(self._read_file(source_file))
        target_blocks = parse_content_into_blocks(self._read_file(target_path))
        
        # Verify block structure integrity
        if len(source_blocks) != len(target_blocks):
            logger.log_warning(f"Block count mismatch in {target_path}. Restoring from source.")
            shutil.copy2(source_file, target_path)
            return
            
        # Map blocks by ID
        source_block_map = {generate_block_id(b['content']): b for b in source_blocks}
        target_block_map = {generate_block_id(b['content']): b for b in target_blocks}
        
        # Check for unauthorized block additions/deletions
        if set(source_block_map.keys()) != set(target_block_map.keys()):
            logger.log_warning(f"Unauthorized block modification in {target_path}. Restoring from source.")
            shutil.copy2(source_file, target_path)
            return
            
        # Preserve modified target blocks while syncing source changes
        self._merge_and_save_blocks(source_blocks, target_blocks, target_path)

    def _read_file(self, file_path):
        """Read the contents of a file and return it as a string."""
        with open(file_path, 'r', encoding='utf-8') as f:
            return f.read()    
        def _handle_deleted_files(self, logger, source_files):
            for target_dir in self.target_dirs:
                for root, _, files in os.walk(target_dir):
                    for file in files:
                        if file.endswith('.md'):
                            rel_path = os.path.relpath(os.path.join(root, file), target_dir)
                            if rel_path not in source_files:
                                target_file = os.path.join(root, file)
                                mod_time = os.path.getmtime(target_file)
                                logger.log_file_deletion(rel_path, mod_time)
                                os.remove(target_file)
                                meta_file = os.path.join(self.meta_dir, file + '.meta')
                                if os.path.exists(meta_file):
                                    os.remove(meta_file)

class TargetUpdater:
    # Existing methods...

    def _merge_and_save_blocks(self, source_blocks, target_blocks, target_path):
        merged_content = []

        for source_block in source_blocks:
            block_id = generate_block_id(source_block['content'])
            target_block = next((b for b in target_blocks if generate_block_id(b['content']) == block_id), None)

            if target_block:
                # Preserve modifications in the target block if allowed
                if target_block.get('modified_in_target', False):
                    merged_content.append(target_block['content'])
                else:
                    merged_content.append(source_block['content'])
            else:
                # If no matching target block, use the source block
                merged_content.append(source_block['content'])

        # Write the merged content back to the target file
        with open(target_path, 'w', encoding='utf-8') as f:
            f.write('\n'.join(merged_content))
