#!/bin/bash
# delete the date in filename.

# Function to process filename
rename_file() {
    local file="$1"
    # Match date pattern YYYY-MM-DD or YYYY-M-D
    if [[ $file =~ ^([0-9]{4}-[0-9]{1,2}-[0-9]{1,2})-(.+)$ ]]; then
        # Extract the part after date prefix
        new_name="${BASH_REMATCH[2]}"
        if [ "$file" != "$new_name" ]; then
            echo "Renaming: $file -> $new_name"
            mv -v "$file" "$new_name"
        fi
    fi
}

# Process all .md files in current directory and subdirectories
find . -type f -name "*.md" | while read -r filepath; do
    dir=$(dirname "$filepath")
    file=$(basename "$filepath")
    (
        cd "$dir" || exit
        rename_file "$file"
    )
done
