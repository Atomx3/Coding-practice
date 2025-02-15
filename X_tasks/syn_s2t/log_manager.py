import os
import time
import logging
from typing import List

class LogManager:
    def __init__(self):
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(levelname)s - %(message)s'
        )
        self.file_changes = []
        self.deleted_files = set()
        
    def initialize_logging(self):
        self.file_changes.clear()
        self.deleted_files.clear()
        logging.info("Starting syncing...")
        
    def log_file_change(self, mod_time: float, rel_path: str, change_type: str):
        message = f"{change_type} file: {rel_path}"
        self.file_changes.append((mod_time, message))
        
    def log_file_deletion(self, rel_path: str, mod_time: float) -> bool:
        if rel_path not in self.deleted_files:
            self.deleted_files.add(rel_path)
            message = f"Deleted file: {rel_path}"
            self.file_changes.append((mod_time, message))
            return True
        return False
        
    def log_sync_result(self, target_dirs: List[str], sync_success: bool, sync_errors: List[str]):
        # Only log changes once, sorted by modification time
        for _, message in sorted(self.file_changes, key=lambda x: x[0]):
            logging.info(message)
            
        target_dirs_str = ', '.join(f"{d}/" for d in target_dirs)
        if sync_success:
            logging.info(f"syncing to {target_dirs_str} success!")
        else:
            logging.info(f"syncing to {target_dirs_str} fail, reasons: {', '.join(sync_errors)}!")