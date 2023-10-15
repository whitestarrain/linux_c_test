#include <stdio.h>

#define CONCAT(a, b) a##b
#define HASH_HASH # ## #

int main(int argc, char* argv[])
{
    char ab[] = "ab";
    printf(CONCAT(a, b));
    return 0;
}
