#include <stdio.h>

// 一个字节指针引用一个字节序列，其中每个字节都被认为是一个非负整数
typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; i++) {
        printf("%.2x", start[i]);
    }
    printf("\n");
}

void int_to_char()
{
    union int_chart
    {
        int  a;
        char b;
    } u2;
    u2.a = 1;
    /**
     * 4字节值,右侧为低位 00 00 00 01
     * 从低地址到高地址
     *   若为大端,低地址为高位, 为 00 00 00 01
     *   若为小端,低地址为低位, 为 01 00 00 00
     */
    // char为一个字节,默认占用低位地址的第一个字节. 待验证
    printf("%d \n", u2.b == 1);
}

void printf_bin(int num)
{
    int i, j, k;
    // p先指向num后面第3个字节的地址，即num的最高位字节地址
    unsigned char* p = (unsigned char*)&num + 3;

    for (i = 0; i < 4; i++) {
        // 依次处理4个字节(32位）
        // 取每个字节的首地址，从高位字节到低位字节，即p p-1 p-2 p-3地址处
        j = *(p - i);

        for (int k = 7; k >= 0; k--)

        {
            // 处理每个字节的8个位，注意字节内部的二进制数是按照人的习惯存储！
            if (j & (1 << k))
                // 1左移k位，与单前的字节内容j进行或运算，如k=7时，00000000&10000000=0
                // ->该字节的最高位为0
                printf("1");
            else
                printf("0");
        }
        printf(" ");
        // 每8位加个空格，方便查看
    }
    printf("\r\n");
}

/**
 * bit-filed 存放位置解析
 */
int main(int argc, char* argv[])
{
    union one_byte
    {
        struct
        {
            unsigned int bit0 : 4;
            unsigned int bit1 : 4;
            unsigned int bit2 : 4;
            unsigned int bit3 : 4;
        } bitfield;
        unsigned char  byte[2];
        unsigned short sht;
    };
    // 0001 0110 1000 1111
    union one_byte u = {{1, 6, 8, 15}};
    // 00010010 01001000
    printf("value: %u, %u, %u, %u \n",
           u.bitfield.bit0,
           u.bitfield.bit1,
           u.bitfield.bit2,
           u.bitfield.bit3);
    // value: 1, 6, 8, 15

    printf("char value: %d, %d \n", u.byte[0], u.byte[1]);
    // char value: 97, 248
    printf("hex dump: %.2x, %.2x \n", u.byte[0], u.byte[1]);
    // hex dump: 61, f8
    // 内存中,地址从低到高 0110 0001 1111 1000
    printf("sht value: %d \n", u.sht);
    // sht value: 63585
    // 11111000 01100001
    // 高地址作高位,小端

    /*
    解析:
    地址和小端是针对字节的,
  在一个字节的内部的8位2进制数，都是按照人类的习惯从左到右存放，如00000010
    小端下,下图为调用栈,地址从从下到上升高
    ** bit 位先从低地址的低位开始塞 **
    ┌─────────┐
  ▲ │1111 1000│
  │ ├─────────┤
  │ │0110 0001│
    └─────────┘
    最终地址从低到高,为:
    01100001 11111000
  */

    return 0;
}
