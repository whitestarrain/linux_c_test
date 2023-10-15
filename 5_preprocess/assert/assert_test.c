#include "assert.h"

#undef DEBUG
#define DEBUG

int main(int argc, char *argv[])
{
    int a=1,b=2;
    assert(a>b);
    return 0;
}
