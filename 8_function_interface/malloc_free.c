#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int   number;
    char *msg;
} unit_t;


int main(int argc, char *argv[])
{
    unit_t *p = malloc(sizeof(unit_t));
    if (p == NULL) {
        printf("out of memory \n");
        exit(1);
    }
    p->number = 0;
    p->msg    = malloc(20);
    stpcpy(p->msg, "hello world\n");
    printf("number: %d, msg: %s", p->number, p->msg);
    free(p->msg);
    free(p);
    p = NULL;
    return 0;
}
