#include <stdio.h>
#define print_expr(expr)                 \
    do {                                 \
        printf("%s :%d\n", #expr, expr); \
    } while (0);

int main(int argc, char *argv[])
{
    int  array[] = {1, 2, 3, 4};
    int *p1      = array;
    int *p2      = &array[0];
    // array[index] == *(array+index) == *(index+array) == index[array]
    print_expr(array[1]);
    print_expr(p1[1]);
    print_expr(p2[1]);
    print_expr(1 [p1]);
    print_expr(1 [p2]);
    return 0;
}
