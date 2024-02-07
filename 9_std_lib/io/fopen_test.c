#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen("./temp/test.txt", "w+");
    if (f == NULL) {
        printf("open file error");
        exit(1);
    }
    fclose(f);
    return EXIT_SUCCESS;
}
