# !/bin/bash #  shebang 行，用于指定脚本应使用的解释器

# 在 Shell 脚本中，使用 # 添加注释；
# 使用 \ 将很长的行切成多行；

printf "%s\n%s\n%s\n" \
"This is a sample test case" \
"it checks your program's one argument behavior" \
"go!" \
| tee | ./sortLines # 将数据传递给 sortLines 程序
