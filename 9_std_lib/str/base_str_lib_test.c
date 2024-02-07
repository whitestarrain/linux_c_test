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

void *my_memcpy(void *dest, const void *src, size_t n)
{
    char       *d               = dest;
    const char *s               = src;
    int         single_char_num = n % 4;
    while (single_char_num--) {
        *(d++) = *(s++);
    }
    int        four_char_num = n / 4;
    int       *int_dest_p    = (int *)d;
    const int *int_src_p     = (const int *)s;
    while (four_char_num--) {
        *(int_dest_p++) = *(int_src_p++);
    }
    return dest;
}

void memcpy_test()
{
    char dest[10];
    char src[20] = "hello world";
    dest[9]      = '\0';
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

void strcat_test()
{
    char s1[10] = "ab";
    char s2[10] = "cd";
    logger("%s", strcat(s1, s2));
    logger("%s", strncat(s1, s2, 3));
}

void strcmp_test()
{
    logger("%d", strcmp("aaa", "bbb"));
}

void strstr_test()
{
    logger("%s", strstr("aabbcc", "bc"));
}

void strtok_test()
{
    char s[10]     = "aa,bb:cc";
    char *delim = ",:";
    char *token = strtok(s, delim);
    logger("%s", token);
    while ((token = strtok(NULL, delim)) != NULL) {
        logger("%s", token);
    }
    logger("%s", token);
}

void memmove_test() {}

// posix interface
void strdup_test() {}

int main(int argc, char *argv[])
{
    memset_test();
    memcpy_test();
    strcat_test();
    strcmp_test();
    strstr_test();
    strtok_test();
    return 0;
}
