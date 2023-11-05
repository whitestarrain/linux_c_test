#include <stdio.h>
#include <string.h>

static const char *msg[] = {"Sunday",
                            "Monday",
                            "Tuesday",
                            "Wednesday",
                            "Thursday",
                            "Friday",
                            "Saturday"};

char *get_a_day(int idx)
{
    // static，分配在data segment中，而不是栈中
    static char buf[20];
    strcpy(buf, msg[idx]);
    return buf;
}

int a[5];
int (*reture_array_ptr(void *str))[]
{
    printf("Hello %s\n", (const char *)str);
    return &a;
}

int main(int argc, char *argv[])
{
    printf("%s %s\n", get_a_day(0), get_a_day(1));
    return 0;
}
