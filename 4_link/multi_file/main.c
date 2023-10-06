/* main.c */
#include <stdio.h>

extern void push(char);
extern char pop();
extern int  is_empty();

int a, b = 1;

int main(void)
{
    push('a');
    push('b');
    push('c');

    while (!is_empty()) putchar(pop());
    putchar('\n');

    return 0;
}
