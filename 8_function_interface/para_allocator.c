// 通过两层指针分配内存

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int   number;
    char *msg;
} unit_t;

void alloc_unit(unit_t **p)
{
    unit_t *p_t = malloc(sizeof(unit_t));
    if (p_t == NULL) {
        printf("out of memory");
        return;
    }
    p_t->number = 10;
    p_t->msg    = malloc(20);
    stpcpy(p_t->msg, "hello world");

    *p = p_t;
}
void free_unit(unit_t **p)
{
    if (p == NULL) {
        return;
    }
    free((*p)->msg);
    free((*p));
    return;
}

int main(int argc, char *argv[])
{
    unit_t *p = NULL;
    alloc_unit(&p);
    printf("%s", p->msg);
    return EXIT_SUCCESS;
}
