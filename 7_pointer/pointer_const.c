#include <stddef.h>

int main(int argc, char *argv[])
{
    char   c  = 'a';
    char  *p1 = &c;
    char **p2 = &p1;

    const char **pp1 = p2;
    char const **pp1_2 = p2;
    // **pp1            = 'b';        // error

    char *const *pp2 = p2;
    // *pp2             = *pp2 + 1;   // error

    char **const pp3 = p2;
    // pp3              = pp3;        // error


    const char *const *const pp4 = p2;
    // pp3              = pp3;        // error
}
