#undef MACHINE
#define MACHINE 8086

#if MACHINE == 68000
    int x;
#elif MACHINE == 8086
    long x;
#else
    #error UNKNOWN TARGET MACHINE
#endif /* MACHINE */


#define VERSION 2
// #define VERSION 4

#if defined x || y || VERSION < 3

#endif /* VERSION */

