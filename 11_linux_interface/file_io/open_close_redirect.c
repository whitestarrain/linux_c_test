#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char *output1 = "stand output part 1\n";
    write(STDOUT_FILENO, output1, strlen(output1));

    char *output2 = "stand output part 2\n";
    printf("%s", output2);
    fflush(stdout);   // necessary, print write to c io buffer

    // 重定向 stdout
    close(1);
    int fid = open("temp/std1.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);

    // 向stdout写入
    printf("fd:%d, stand output part 3", fid);
}
