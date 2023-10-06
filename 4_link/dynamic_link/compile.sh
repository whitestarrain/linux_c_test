#/bin/bash

rm -rf /root/project/linux-c-src/4_link/dynamic_link/{main,*.{a,o,so}}

# compile "Position Independent Code" Object file
gcc -c -g -fPIC stack/pop.c stack/push.c stack/stack.c stack/is_empty.c
# generate dynamic library
gcc -shared -o libstack.so stack.o push.o pop.o is_empty.o
# compile main and link libstack
gcc main.c -g -L. -lstack -Istack -omain

LD_LIBRARY_PATH=. ./main
echo $?
