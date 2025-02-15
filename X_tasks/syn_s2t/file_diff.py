import os
import filecmp
import difflib
# compare multiple target_dirs with source_dir.

def compare_files(file1, file2):
    """Compare two files and return the differences."""
    with open(file1, 'r', encoding='utf-8') as f1, open(file2, 'r', encoding='utf-8') as f2:
        file1_lines = f1.readlines()
        file2_lines = f2.readlines()

    # Use difflib to get differences
    diff = difflib.unified_diff(
        file1_lines, file2_lines,
        fromfile=file1, tofile=file2,
        lineterm=''
    )
    # Filter out unchanged lines and return only differences
    return [line for line in diff if line.startswith(('+', '-', '@'))]

def compare_directories(source_dir, *target_dirs):
    return is_directories_synced(source_dir, *target_dirs)

def is_directories_synced(source_dir, *target_dirs):
    all_synced = True
    
    for target_dir in target_dirs:
        source_files = {os.path.relpath(os.path.join(root, f), source_dir)
                       for root, _, files in os.walk(source_dir)
                       for f in files if f.endswith('.md')}
        
        target_files = {os.path.relpath(os.path.join(root, f), target_dir)
                       for root, _, files in os.walk(target_dir)
                       for f in files if f.endswith('.md')}
        
        # Show files that exist in source but not in target
        missing_in_target = source_files - target_files
        if missing_in_target:
            print(f"\nFiles missing in {target_dir}:")
            for file in missing_in_target:
                print(f"- {file}")
            all_synced = False
            
        # Show files that exist in target but not in source
        extra_in_target = target_files - source_files
        if extra_in_target:
            print(f"\nExtra files in {target_dir}:")
            for file in extra_in_target:
                print(f"- {file}")
            all_synced = False
            
        # Compare content of files that exist in both directories
        common_files = source_files & target_files
        for file_path in common_files:
            source_file = os.path.join(source_dir, file_path)
            target_file = os.path.join(target_dir, file_path)
            differences = compare_files(source_file, target_file)
            if differences:
                print(f"\nContent differences in {file_path}:")
                for diff in differences:
                    print(diff)
                all_synced = False
    
    if all_synced:
        print("\nAll directories are identical")
    return all_synced
def main():
    source_dir = './zh'
    target_dirs = ['./en', './ru']
    
    print("Starting directory comparison...")
    print(f"Source directory: {source_dir}")
    print(f"Target directories: {target_dirs}")
    
    # First verify source directory exists
    if not os.path.exists(source_dir):
        print(f"Source directory not found: {source_dir}")
        return
        
    for target_dir in target_dirs:
        if not os.path.exists(target_dir):
            print(f"Target directory not found: {target_dir}")
            continue
            
        print(f"\nComparing {target_dir} with source:")
        is_directories_synced(source_dir, target_dir)

if __name__ == "__main__":
    main()