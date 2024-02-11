#include <unistd.h>

char msg[14] = "Hello,world\n";
#define len 14

int main()
{
    write(1,msg,len);
    _exit(0);
}
