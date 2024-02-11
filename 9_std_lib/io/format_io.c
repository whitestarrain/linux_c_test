#include <stdarg.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // printf, fprintf, sprintf, snprintf
    printf("%s\n", "test");
    char buffer[10];
    int  l = snprintf(buffer, sizeof(buffer), "%s", "aa");
    printf("%s,%d\n", buffer, l);

    // vprintf, vfprintf, vsprintf, vsnprintf

    // scanf sscanf fscanf
    int a;
    scanf("%d", &a);
    printf("%d", a);

    // vscanf vsscanf vfscanf
}
