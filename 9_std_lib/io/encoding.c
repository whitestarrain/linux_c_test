#include <stdio.h>
#include <stdlib.h>

typedef unsigned char *byte_pointer;

/**
 *  一个字节指针引用一个字节序列，其中每个字节都被认为是一个非负整数
 */
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
    static char hello_cn[] = "你好";
    printf("%s\n", hello_cn);
    unsigned char *p = hello_cn;
    show_bytes(p, sizeof(hello_cn));
    return EXIT_SUCCESS;
}
