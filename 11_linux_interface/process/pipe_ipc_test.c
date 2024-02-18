#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLINE 80

int main(int argc, char *argv[])
{
    pid_t pid;
    int   fd[2];
    // C89规定，在任何执行语句之前，在块的开头声明所有局部变量。
    // 在C99以及C++中则没有这个限制，即在首次使用之前，可在块的任何位置都可以声明变量。
    // 无论放到那里，最后编译出来的代码都是一样的
    char  line[MAXLINE];
    int   n;
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    if (pid > 0) {   // parent
        close(fd[0]);
        char msg[] = "hello world\n";
        write(fd[1], msg, strlen(msg));
    }
    else {   // child
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
    }
    return EXIT_SUCCESS;
}
