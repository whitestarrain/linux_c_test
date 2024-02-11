#include <stdlib.h>

int main(int argc, char *argv[])
{
    // calloc, realloc

    // realloc(NULL, size) == malloc(size)
    // realloc(ptr, 0) == free(ptr)

    // alloca: alloc memory in stack, don't need free [posix]
}
