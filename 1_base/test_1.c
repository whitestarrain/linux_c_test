#include <stdio.h>

void printBits(size_t const size, void const* const ptr);

/**
 * why not 0xffff
 * + 优先级 高于 <<
 */
int main(int argc, char* argv[])
{
    int          i    = 0;
    unsigned int sum  = 0;
    unsigned int sum2 = 0;
    for (; i < 16; i++) {
        sum  = sum + 1U << i;
        sum2 = sum2 + (1U << i);
    }
    printBits(sizeof(sum), &sum);
    printBits(sizeof(sum2), &sum2);
}

/**
 * print binary
 */
void printBits(size_t const size, void const* const ptr)
{
    unsigned char* b = (unsigned char*)ptr;
    unsigned char  byte;
    int            i, j;

    for (i = size - 1; i >= 0; i--) {
        for (j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}
