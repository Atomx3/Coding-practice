#!/bin/bash
# delete files
# find . -name "file_name" -type f -exec rm -f {} +
# run the script in terminal zhs ```./script.sh```

find . -name ".DS_Store" -type f -exec rm -f {} +
echo "delete all ！"#statement"！"
