#include "../../0_header/log.h"
#include <stdio.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/**
 * base string function
 */

void memset_test()
{
    char s[10] = "";
    logger("%s", s);
    memset(s, 0, sizeof(s));
    logger("%s", s);
    s[0] = 'a';
    logger("%lu", strlen(s));
}

void memcpy_test()
{
    char dest[10];
    char src[20] = "hello world";
    dest[9] = '\0';
    logger("%s", dest);
    logger("%s", src);
    logger("%lu", sizeof(dest));
    logger("%s", (char *)memcpy(dest, src, sizeof(dest) - 1));

    char hello[20] = "hello world\n";
    logger("%s", hello);
    memcpy(hello + 1, hello, 13);
    logger("%s", hello);

    // char buf[20] = "hello world\n";
    // memcpy(buf + 1, buf, 13);
    // logger("%s", buf);
}

void memmove_test() {}

// posix interface
void strdup_test() {}

int main(int argc, char *argv[])
{
    memset_test();
    memcpy_test();
    return 0;
}
