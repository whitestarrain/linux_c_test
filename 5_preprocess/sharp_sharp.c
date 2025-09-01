#include <stdio.h>

#define CONCAT(a, b) a##b##_concat
#define HASH_HASH # ## #

int main(int argc, char* argv[])
{
    char ab_concat[] = "ab";
    printf(CONCAT(a, b));
    return 0;
}
