#include <stdarg.h>
#include <stdio.h>

void myprintf(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    char c;
    while ((c = *format++)) {
        switch (c) {
        case 'c':
        {
            char ch = va_arg(ap, int);
            putchar(ch);
            break;
        }
        case 's':
        {
            char *p = va_arg(ap, char *);
            fputs(p, stdout);
            break;
        }
        default:
        {
            putchar(c);
        }
        }
    }
    va_end(ap);
}

int main(int argc, char *argv[])
{
    myprintf("c\ts\n", '1', "hellow");
}
