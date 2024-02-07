#include <stdio.h>
#include <stdlib.h>

char *my_strtok_r(char *restrict str, char *restrict delim,
                  char **restrict saveptr)
{
    if (str == NULL || delim == NULL) return NULL;
    char *start_point = str;
    if (*saveptr != NULL) {
        start_point = *saveptr;
    }
    int i;
    for (i = 0; *(start_point + i); i++) {
        int j;
        for (j = 0; *(delim + j); j++) {
            if (*(start_point + i) == *(delim + j)) {
                *saveptr           = start_point + i + 1;
                *(start_point + i) = '\0';
                return start_point;
            }
        }
    }
    *saveptr = start_point + i;
    return start_point;
}


int main(int argc, char *argv[])
{
    char *saveptr = NULL;
    char  str[]   = "aa;bb";
    printf("%s", my_strtok_r(str, ";", &saveptr));
    printf("%s", my_strtok_r(str, ";", &saveptr));
    return EXIT_SUCCESS;
}
