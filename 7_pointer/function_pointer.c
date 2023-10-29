#include <stdio.h>

void say_hello(const char *str, int num)
{
    for (int i = 0; i < num; i++) {
        printf("hello, %s\n", str);
    }
}

int main(int argc, char *argv[])
{
    void (*f)(const char *, int) = say_hello;
    f("Guys", 2);
    return 0;
}
