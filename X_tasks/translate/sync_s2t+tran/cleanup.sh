#!/bin/bash

# 查找并删除所有 .DS_Store 文件
find . -name ".DS_Store" -exec rm {} \;

echo "All .DS_Store files have been deleted."
