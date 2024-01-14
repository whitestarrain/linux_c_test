#include <stdio.h>
#include <string.h>

char *my_strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) dest[i] = src[i];
    for (; i < n; i++) dest[i] = '\0';
    return dest;
}

char *shrink_space(char *dest, const char *src, size_t n)
{
    return dest;
};

int main(int argc, char *argv[])
{
    char buf[10];
    strcpy(buf, "hello");
    printf("%s\n", buf);

    // overlap
    // char str[4] = "hell";
    // strcpy(buf, str);
    // printf("%s\n", buf);
    strncpy(buf, "hello world", sizeof(buf) - 1);
    printf("buf: %s\n", buf);

    char *s = "This Content hoho  \n   \n  \r is ok ok? \t file system uttered "
              "words \t  ok ok      ? end.";
    // if don't assign a value of '' for the array in stack, the buf2 value will be random
    // static array default is a list of '\0'. (because the .bss section)
    char  buf2[30] = "";
    printf("buf2: %s\n", buf2);
    printf("%s\n", shrink_space(buf2, s, sizeof(buf2)));
    return 0;
}
