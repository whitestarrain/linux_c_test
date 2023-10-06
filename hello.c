#include <stdio.h>

int foo(int* arrP)
{
    printf("%d", arrP[0]);
    return 0;
}

int main(int argc, char* argv[])
{
    printf("hello world");
    int arr[] = {1, 2, 3};
    foo(arr);
    return 0;
}
