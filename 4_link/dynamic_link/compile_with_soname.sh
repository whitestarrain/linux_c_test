#!/bin/bash

rm -rf ./{main,*.{a,o,so},*.so.*}

# compile "Position Independent Code" Object file
gcc -c -g -fPIC stack/pop.c stack/push.c stack/stack.c stack/is_empty.c
# specify soname
gcc -shared -Wl,-soname,libstack.so.1 -o libstack.so.1.0 pop.o push.o stack.o is_empty.o
# compile just find library by linker name

# compiler need linker name
ln -s $(pwd)/libstack.so.1.0 $(pwd)/libstack.so
# run need soname
ln -s $(pwd)/libstack.so.1.0 $(pwd)/libstack.so.1
# compile main and link libstack
gcc main.c -g -L. -lstack -Istack -omain

ldd main

# or edit /etc/ld.so.conf, add current path
# and run `sudo ldconfig -v`
LD_LIBRARY_PATH=. ./main
echo $?
