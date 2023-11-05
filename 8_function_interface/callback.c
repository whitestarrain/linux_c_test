#include <stdio.h>
#include <stdlib.h>

typedef void (*func)(void *);

void repeat_three(func f, void *para)
{
    for (int i = 0; i < 3; i++) {
        f(para);
    }
}

void say_hello(void *str)
{
    printf("Hello %s\n", (const char *)str);
}

void count_number(void *num)
{
    for (int i = 0; i < *((int *)num); i++) {
        printf("%d", i);
    }
    putchar('\n');
}

int main(int argc, char *argv[])
{
    repeat_three(say_hello, "world");
    int i = 5;
    repeat_three(count_number, &i);
    return EXIT_SUCCESS;
}
