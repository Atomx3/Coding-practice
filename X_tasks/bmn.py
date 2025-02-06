import os
import re

def rename_files(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            old_name = os.path.join(root, file)
            base_name, ext = os.path.splitext(file)
            new_base_name = re.sub(r'\s[a-f0-9]{32}$', '', base_name)
            new_name = os.path.join(root, new_base_name + ext)

            if old_name != new_name:
                print(f'Renaming: {old_name} -> {new_name}')
                os.rename(old_name, new_name)

if __name__ == '__main__':
    directory = '.'  # 可以将此处改为目标目录
    rename_files(directory)
