#include <stdio.h>
#define sh(x) printf("n" #x "=%d, or %d\n",n##x,alt[x])
#define sub_z 2

int main(int argc, char *argv[])
{
    int nsub_z = 10;
    char alt[] = "alt";
    sh(sub_z);
    return 0;
}

