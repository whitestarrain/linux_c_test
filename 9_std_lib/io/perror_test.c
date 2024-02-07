#include "../../0_header/log.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *f = fopen("abcde", "r");
    if (f == NULL) {
        perror("open file abcde");
        logger("errno: %d", errno);
        logger("%s", strerror(errno));
        // exit(1);
    }

    FILE *shadow = fopen("/etc/shadow", "r");
    if (shadow == NULL) {
        perror("open /etc/shadow:");
    }

    return EXIT_SUCCESS;
}
