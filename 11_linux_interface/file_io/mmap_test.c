#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#define DATA "hello world \n"

void create_test_file()
{
    FILE *f = fopen("temp/hello.txt", "w+");
    fputs(DATA, f);
    fflush(f);
}

int main(int argc, char *argv[])
{

    int *p;
    int  fd = open("temp/hello.txt", O_RDWR);
    if (fd < 0) {
        perror("open temp/hello.txt");
        exit(1);
    }
    p = mmap(NULL, strlen(DATA), PROT_WRITE, MAP_SHARED, fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // modify file throw pinter
    // int type pointer, modify four char
    p[0] = 0x30313233;

    munmap(p, 6);

    return EXIT_SUCCESS;
}
