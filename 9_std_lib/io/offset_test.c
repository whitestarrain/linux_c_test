#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    if ((fp = fopen("./temp/test.txt", "r+")) == NULL) {
        perror("open file ./temp/test.txt");
        exit(1);
    }
    if (fseek(fp, 2, SEEK_SET) != 0) {
        perror("seek file temp/test.txt");
        exit(1);
    }
    fputc('k', fp);
    fclose(fp);
    return EXIT_SUCCESS;
}
