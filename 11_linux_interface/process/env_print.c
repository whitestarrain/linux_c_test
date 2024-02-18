#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    extern char **environ;
    int           i;
    for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
    printf("\n%s\n", getenv("PATH"));

    setenv("ENV_TEST1", "sss", 0);
    printf("\n%s\n", getenv("ENV_TEST1"));
    return EXIT_SUCCESS;
}
