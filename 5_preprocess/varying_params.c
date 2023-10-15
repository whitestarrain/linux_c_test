#include <stdio.h>

#define showlist(...) printf(#__VA_ARGS__)
#define report(test, ...) ((test) ? printf(#test) : printf(__VA_ARGS__))

int main(int argc, char* argv[])
{
    showlist("first", "second", "third");
    printf("\n");
    int x = 0, y = 1;
    report(y > x, "x is %d but y is %d", x, y);
    printf("\n");
    report(x > y, "x is %d but y is %d", x, y);
}
