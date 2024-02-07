#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // fgetc(stdin) == getchar
    // fputc(stdout) == putchar

    FILE *f = fopen("./temp/test.txt", "w+");
    if (f == NULL) {
        perror("open file ./temp/test.txt \n");
        exit(1);
    }
    int ch;
    while ((ch = getchar()) != EOF) {
        fputc(ch, f);
    }
    rewind(f);
    while ((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }
    fclose(f);
    return EXIT_SUCCESS;
}
