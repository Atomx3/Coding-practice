import subprocess
import os
from meta_data_manager import generate_block_id

class GitManager:
    def __init__(self, repo_dir, source_dir):
        self.repo_dir = repo_dir
        self.source_dir = source_dir
        
    def initialize_git(self):
        if not os.path.exists(os.path.join(self.repo_dir, '.git')):
            subprocess.run(['git', 'init'], cwd=self.repo_dir, check=True)
            self._create_gitignore()
            
    def _create_gitignore(self):
        gitignore_path = os.path.join(self.repo_dir, '.gitignore')
        with open(gitignore_path, 'w') as f:
            f.write('*\n')
            f.write('!source_dir/\n')
            
    def get_changes(self):
        return {
            'modified': self._get_changed_files(),
            'diff': self._get_file_diff(),
            'moved': self._get_moved_files()
        }

    def _get_changed_files(self):
        result = subprocess.run(
            ['git', 'status', '--porcelain', self.source_dir],
            cwd=self.repo_dir,
            capture_output=True,
            text=True
        )
        changed_files = []
        for line in result.stdout.splitlines():
            status = line[:2]
            file_path = line[3:]
            if status in ['M ', 'A ', 'D ']:  # Modified, Added, Deleted
                changed_files.append(file_path)
        return changed_files

    def _get_file_diff(self):
        result = subprocess.run(
            ['git', 'diff', '--cached', '--', self.source_dir],
            cwd=self.repo_dir,
            capture_output=True,
            text=True
        )
        return result.stdout

    def _get_moved_files(self):
        result = subprocess.run(
            ['git', 'status', '--porcelain', '--', self.source_dir],
            cwd=self.repo_dir,
            capture_output=True,
            text=True
        )
        moved_files = []
        for line in result.stdout.splitlines():
            if line.startswith('R'):
                _, old_path, new_path = line.split()
                moved_files.append((old_path, new_path))
        return moved_files

def parse_diff(diff_output: str) -> dict:
    changes = {
        'blocks': {
            'added': [],
            'modified': [],
            'deleted': []
        },
        'files': {
            'added': [],
            'modified': [],
            'deleted': []
        }
    }
    current_file = None
    for line in diff_output.splitlines():
        if line.startswith('diff --git'):
            current_file = line.split(' b/')[-1]
            changes['files']['modified'].append(current_file)
        elif line.startswith('+') and not line.startswith('+++'):
            block_content = line[1:]
            block_id = generate_block_id(block_content)
            changes['blocks']['added'].append({
                'id': block_id,
                'content': block_content,
                'file': current_file
            })
        elif line.startswith('-') and not line.startswith('---'):
            block_content = line[1:]
            block_id = generate_block_id(block_content)
            changes['blocks']['deleted'].append({
                'id': block_id,
                'content': block_content,
                'file': current_file
            })
    return changes

def get_changed_files(repo_dir, source_dir):
    result = subprocess.run(
        ['git', 'status', '--porcelain', source_dir],
        cwd=repo_dir,
        capture_output=True,
        text=True
    )
    changed_files = []
    for line in result.stdout.splitlines():
        status = line[:2]
        file_path = line[3:]
        if status != '??':
            changed_files.append(file_path)
    return changed_files

def ensure_directory_structure(source_dir, target_dir):
    """Ensure target directory matches source directory structure"""
    for root, dirs, files in os.walk(source_dir):
        relative_path = os.path.relpath(root, source_dir)
        target_path = os.path.join(target_dir, relative_path)
        os.makedirs(target_path, exist_ok=True)