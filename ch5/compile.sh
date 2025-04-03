#!/bin/bash

# 检查参数是否存在
if [ $# -ne 1 ]; then
    echo "用法: $0 <filename.c>"
    exit 1
fi

# 获取输入参数
c_file="$1"

# 检查文件是否存在
if [ ! -f "$c_file" ]; then
    echo "错误: 文件 $c_file 不存在"
    exit 1
fi

# 检查文件扩展名
if [[ "$c_file" != *.c ]]; then
    echo "错误: 必须指定.c文件"
    exit 1
fi

# 提取文件名（不含扩展名）
executable_name=$(basename "$c_file" .c)

# 编译命令
gcc -o "$executable_name" "$c_file"

# 添加可执行权限
chmod +x "$executable_name"

echo "已编译: $c_file -> $executable_name"
