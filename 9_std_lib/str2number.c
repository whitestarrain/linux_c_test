#include "../0_header/log.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void test()
{
    logger("%d", atoi("20"));
    logger("%d", atoi("20abc"));
    logger("%d", atoi("ss20aa"));
    logger("%f", atof("20.1"));
    logger("%f", atof("a20.1"));
    logger("%f", atof("20.1a"));
    logger("%f", atof("a20a.1a"));

    char *pos;
    logger("%ld", strtol("20aa", &pos, 10));
    logger("%s", pos);

    logger("%lf", strtod("20.1aa", &pos));
    logger("%s", pos);
}

int main(int argc, char *argv[])
{
    int   base;
    char *endptr, *str;
    long  val;
    if (argc < 2) {
        fprintf(stderr, "Usage: %s str [base] \n", argv[0]);
        exit(EXIT_FAILURE);
    }
    str  = argv[1];
    base = (argc > 2) ? atoi(argv[2]) : 10;

    errno = 0;
    val   = strtol(str, &endptr, base);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) ||
        errno != 0 && val == 0) {
        perror("strtol");
        exit(EXIT_FAILURE);
    }

    if (endptr == str) {
        fprintf(stderr, "No digits were found");
        exit(EXIT_FAILURE);
    }

    printf("strtol() return %ld\n", val);
    if (*endptr != '\0') {
        printf("Futher characters after number: %s\n", endptr);
    }

    exit(EXIT_SUCCESS);
}
