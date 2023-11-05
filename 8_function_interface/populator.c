// 传出参数

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int  number;
    char msg[20];
} unit_t;


void set_unit(unit_t *p)
{
    if (p == NULL) {
        return;
    }
    p->number = 10;
    stpcpy(p->msg, "hello world");
}


int main(int argc, char *argv[])
{
    unit_t t;
    set_unit(&t);
    printf("%s", t.msg);
    return EXIT_SUCCESS;
}
