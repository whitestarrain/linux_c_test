#ifndef LOG_H

#define LOG_H

extern int printf(const char *__restrict __format, ...);
#define _STR(x) #x
#define logger(format, expr)                                              \
    do {                                                                  \
        printf("(line %d) %s: " format "\n", __LINE__, _STR(expr), expr); \
    } while (0)


#endif
