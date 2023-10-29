#include <stdio.h>

int main(int argc, char *argv[])
{
    struct test_struct_pointer
    {
        int  i;
        char c;
    };
    struct test_struct_pointer  s              = {.i = 1, .c = 'a'};
    struct test_struct_pointer *struct_pointer = &s;
    printf("%c", s.c);
    printf("%c", struct_pointer->c);
    return 0;
}
