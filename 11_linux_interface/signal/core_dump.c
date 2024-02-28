#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i = 100;
    while (i--) {
        sleep(1);
    }
    return EXIT_SUCCESS;
}
