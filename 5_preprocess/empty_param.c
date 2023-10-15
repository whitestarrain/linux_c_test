#include <stdio.h>

#define subfix(a) foo##a
#define subfix_3(a, b, c) foo##a##b##c
#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)

int main(int argc, char* argv[])
{
    char foo[] = "foo\n";
    printf(subfix());

    char foos[] = "foos\n";
    printf(subfix(s));

    char fooa[]  = "fooa\n";
    char foob[]  = "foob\n";
    char fooc[]  = "fooc\n";
    char foobc[] = "foobc\n";

    printf(subfix_3(a, , ));
    printf(subfix_3(, a, ));
    printf(subfix_3(, b, ));
    printf(subfix_3(, , c));
    printf(subfix_3(b, c, ));
    printf(subfix_3(, b, c));

    // gcc 扩展语法
    DEBUG("info no.%d\n", 1);
    DEBUG("info");

    return 0;
}
