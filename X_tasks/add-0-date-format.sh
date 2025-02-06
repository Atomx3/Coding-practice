#!/bin/bash
# make date follow format YYYY-MM-DD.
# add 0 ahead of single number date.

# YYYY-M-D  --> YYYY-0M-0D
# YYYY-M-DD --> YYYY-0M-DD
# YYYY-MM-D --> YYYY-MM-0D
#!/bin/bash

# Function to format date
format_date() {
    local date_line="$1"
    if [[ $date_line =~ date:\ ([0-9]{4})-([0-9]{1,2})-([0-9]{1,2}) ]]; then
        year="${BASH_REMATCH[1]}"
        month="${BASH_REMATCH[2]}"
        day="${BASH_REMATCH[3]}"

        # Add leading zeros only if needed
        [[ ${#month} -eq 1 ]] && month="0$month"
        [[ ${#day} -eq 1 ]] && day="0$day"

        echo "date: $year-$month-$day"
    else
        echo "$date_line"
    fi
}

# Process all .md files in current directory and subdirectories
find . -type f -name "*.md" | while read -r file; do
    echo "Processing $file..."
    # Create temporary file
    temp_file=$(mktemp)

    # Process file line by line
    while IFS= read -r line; do
        if [[ $line =~ ^date: ]]; then
            echo "$(format_date "$line")" >> "$temp_file"
        else
            echo "$line" >> "$temp_file"
        fi
    done < "$file"

    # Replace original file
    mv "$temp_file" "$file"
done


# execute the program
# chmod +x up-date-format.sh
# ./up-date-format.sh
