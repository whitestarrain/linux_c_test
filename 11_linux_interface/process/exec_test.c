#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char **my_argv = malloc(sizeof(char *) * 2);
    my_argv[0] = "-a";
    my_argv[1] = "-l";
    // execlp("/usr/bin/ls", "ls", "-l", NULL);
    execvp("ls", my_argv);
    perror("exec ps");
    return EXIT_SUCCESS;
}
