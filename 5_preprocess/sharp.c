// # ## 运算符

#include <stdio.h>
#define STR(s) #s

int main(int argc, char* argv[])
{
    printf(STR(abc:?3\4#));
    printf("\n");
    printf(STR(abc:?\34#));
    printf("\n");
    printf("\n");
    printf(STR("ss"));
    printf("\n");
    printf(STR(strncmp("ab\"c\0d", "abc", '\4"') == 0) STR( : @\n));

    printf(STR((, )));
    // printf(STR(,)); // error
    return 0;
}
