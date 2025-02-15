import os
from log_manager import LogManager
from meta_data_manager import MetaManager
from git_change_tracker import GitManager
from target_file_updater import TargetUpdater

def main_loop(source_dir, target_dirs, repo_dir, meta_dir):
    # Initialize each function modual
    logger = LogManager()
    git_manager = GitManager(repo_dir, source_dir)
    meta_manager = MetaManager(source_dir, target_dirs, meta_dir) 
    target_updater = TargetUpdater(source_dir, target_dirs, meta_dir)
    
    # Execute sync process in order
    logger.initialize_logging()
    git_manager.initialize_git()
    MetaManager(source_dir, target_dirs, meta_dir)
    
    # Detect and handle file moves
    changes = git_manager.get_changes()
    for old_path, new_path in changes.get('moved', []):
        meta_manager.handle_file_move(old_path, new_path)
    
    # Perform file sync operations
    sync_success, sync_errors = target_updater.sync_files(logger)
    
    # Log final results
    logger.log_sync_result(target_dirs, sync_success, sync_errors)
if __name__ == "__main__":
    project_root = os.path.dirname(os.path.abspath(__file__))
    source_dir = './zh'
    target_dirs = ['./en', './ru']
    repo_dir = project_root
    meta_dir = os.path.join(project_root, 'meta')
    
    main_loop(source_dir, target_dirs, repo_dir, meta_dir)