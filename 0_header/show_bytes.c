#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%.2x ", start[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    static char  hello_cn[] = "你好";
    byte_pointer p          = (byte_pointer)hello_cn;
    show_bytes(p, sizeof(hello_cn));
    return EXIT_SUCCESS;
}
