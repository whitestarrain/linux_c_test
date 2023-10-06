#/bin/bash

gcc -c stack/stack.c stack/push.c stac:k/pop.c stack/is_empty.c
ar rs libstack.a stack.o push.o pop.o is_empty.o
gcc main.c -L. -lstack -Istack -o main
