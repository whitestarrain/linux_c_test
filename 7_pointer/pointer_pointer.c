#include <stdio.h>

int main(int argc, char *argv[])
{
    int   i   = 10;
    int  *pi  = &i;
    int **ppi = &pi;
    printf("%d", **ppi);
    return 0;
}
