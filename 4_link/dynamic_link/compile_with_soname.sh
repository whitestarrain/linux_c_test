#/bin/bash

rm -rf /root/project/linux-c-src/4_link/dynamic_link/{main,*.{a,o,so}}

# compile "Position Independent Code" Object file
gcc -c -g -fPIC stack/pop.c stack/push.c stack/stack.c stack/is_empty.c
# specify soname
gcc -shared -Wl,-soname,libstack.so.1 -o libstack.so.1.0 pop.o push.o stack.o is_empty.o
# compile just find library by linker name
ln -s $(pwd)/libstack.so.1.0 $(pwd)/libstack.so
# compile main and link libstack
gcc main.c -g -L. -lstack -Istack -omain

# or edit /etc/ld.so.conf, add current path
# and run `sudo ldconfig -v`
LD_LIBRARY_PATH=. ./main
echo $?
