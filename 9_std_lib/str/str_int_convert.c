#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *int_str = "10";
    int   int_v   = atoi(int_str);
    printf("%d\n", int_v);

    double dou = atof("10.11");
    printf("%f\n", dou);
}
