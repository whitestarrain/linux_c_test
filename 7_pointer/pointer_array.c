#include <stdio.h>

int main(int argc, char *argv[])
{
    int a[10]    = {[2] = 3, [3] = 5};
    int(*pa)[10] = &a;
    printf("%d\n", (*pa)[2]);
    printf("%d\n", pa[0][2]);

    // 注意，下面是错误的，为  *(*(pa+2))，上面的则是  *(*(pa)+2)
    printf("%d\n", *pa[2]);
}
