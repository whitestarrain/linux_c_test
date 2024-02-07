#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen("temp/test.txt", "r");
    // fgets
    char  buffer[10];
    char *res;
    while ((res = fgets(buffer, sizeof(buffer), fp)) != NULL) {
        printf("%s", buffer);
        printf("%s", res);
        printf("%d\n", buffer == res);
    }

    // fputs

    return EXIT_SUCCESS;
}
