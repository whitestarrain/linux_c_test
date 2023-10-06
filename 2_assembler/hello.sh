#!/bin/bash

# 把这个程序保存成文件 hello.s （汇编程序通常以 .s 作为文件名后缀），用汇编器（Assembler）as 把汇编程序中的助记符翻译成机器指令，生成目标文件 hello.o：

as hello.s -o hello.o

# 然后用链接器（Linker，或 Link Editor）ld 把目标文件 hello.o 链接成可执行文件hello：

ld hello.o -o hello

./hello

echo $?
