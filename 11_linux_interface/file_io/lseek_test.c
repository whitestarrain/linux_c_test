#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    off_t curpos;
    curpos = lseek(STDIN_FILENO, 0, SEEK_CUR);
    // return -1 if can't set offset
    printf("%d", (int)curpos);
    return EXIT_SUCCESS;
}
