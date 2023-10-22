#include <stdio.h>
int main(int argc, char *argv[])
{
    // a array contain 10 pointer
    int  *pointer_array[10];
    int **p  = &pointer_array[0];
    int **p1 = pointer_array;

    char a[4][3][2]  = {{{'a', 'b'}, {'c', 'd'}, {'e', 'f'}},
                        {{'g', 'h'}, {'i', 'j'}, {'k', 'l'}},
                        {{'m', 'n'}, {'o', 'p'}, {'q', 'r'}},
                        {{'s', 't'}, {'u', 'v'}, {'w', 'x'}}};
    char(*pa)[2]     = &a[1][0];
    char(*ppa)[3][2] = &a[1];

    // print 'r'
    printf("%c\n", a[2][2][1]);

    // a[2][2][1] => *(*(*(a + 2) + 2) + 1)
    printf("%c\n", *(*(*(a + 2) + 2) + 1));

    // pa => &a[1][0] => &(*(*(a + 1) + 0)) => *(a + 1) + 0 => *(a+1)
    // a == &(*(a+1))-1 == &(pa) - 1
    // a == &(pa) - 1 代入之后可得
    // printf("%c\n", *(*(*(&(pa) - 1 + 2) + 2) + 1)); // error,
    // 指针的地址没有含义
    printf("%c\n", (*(pa + 5))[1]);
    // 等价于
    printf("%c\n", pa[5][1]);

    // &a[1] => &(*(a+1)) => a+1
    // a == (a+1) - 1  == ppa - 1
    // a == ppa -1 代入之后可得：
    printf("%c\n", *(*(*(ppa + 1) + 2) + 1));
    // 等价于
    printf("%c\n", ppa[1][2][1]);

    /*
        pa不能像ppa那样推导，推导dereference，不能加reference，如果要推导：
            pa => &a[1][0] => &(*(*(a + 1) + 0)) => *(a + 1) + 0 => *(a+1)
            a == &(*(a+1))-1 == &(pa) - 1
            a == &(pa) - 1 代入之后可得
            *(*(*(&(pa) - 1 + 2) + 2) + 1)
        其中又 &pa 的操作，但是指针的地址的值本身就是没有意义的

                       ┌──────────┐
        比如：         │          ▼
         ┌─────┬─────┬────┬────┬────┬────┬────┬─────┬─────┐
         │ p1  │     │ p2 │    │ p3 │    │    │     │     │
         └─┬───┴─────┴────┴────┴────┴────┴────┴─────┴─────┘
           │           ▲
           └───────────┘

        p2 == *p1
        p3 == *p2
        但是 &p3 != p2
     */
}
