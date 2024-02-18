#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int ch;
    while ((ch = getchar()) != EOF) {
        putchar(toupper(ch));
    }
    return EXIT_SUCCESS;
}
