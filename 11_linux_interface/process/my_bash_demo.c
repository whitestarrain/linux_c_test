#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* this demo just support one pipe */

void exec_wrap(char *arg_ptr, int *pipe_fds, int pipe_write, int pipe_read)
{
    char  *delim        = " ";
    int    token_number = 0;
    char  *saveptr      = NULL;
    char **token_ptrs   = malloc(sizeof(char *) * strlen(arg_ptr));

    // get exec argvs
    memset(token_ptrs, 0, sizeof(char *) * strlen(arg_ptr) / 2);
    char *token = strtok_r(arg_ptr, delim, &saveptr);
    do {
        token_ptrs[token_number++] = token;
    } while ((token = strtok_r(NULL, delim, &saveptr)) != NULL);

    // redirct, read redirct symbol or use pipe
    char *input_file_ptr  = NULL;
    char *output_file_ptr = NULL;
    int   input_fd        = -1;
    int   output_fd       = -1;
    int   redirct_flag    = 0;
    for (int i = 0; i < token_number; i++) {
        redirct_flag = 0;
        // TODO: 兼容 cat< temp.txt ，当前 重定向符号左边必须要有空格
        if (token_ptrs[i][0] == '<') {
            // 兼容 "<temp.txt" 和 "< temp.txt"
            if (strlen(token_ptrs[i]) > 1) {
                input_file_ptr = token_ptrs[i] + 1;
            }
            else {
                input_file_ptr = token_ptrs[i + 1];
            }
            redirct_flag = 1;
        }
        if (token_ptrs[i][0] == '>') {
            if (strlen(token_ptrs[i]) > 1) {
                output_file_ptr = token_ptrs[i] + 1;
            }
            else {
                output_file_ptr = token_ptrs[i + 1];
            }
            redirct_flag = 1;
        }
        // 截断，不让exec读取到重定向符号后面的参数
        if (redirct_flag) {
            token_ptrs[i] = NULL;
        }
    }

    // redirct's operator precedence is greater than pipeline
    if (input_file_ptr != NULL) {
        input_fd = open(input_file_ptr, O_RDONLY);
    }
    else if (pipe_fds != NULL && pipe_read) {
        input_fd = pipe_fds[0];
        close(pipe_fds[1]);
    }
    if (output_file_ptr != NULL) {
        output_fd = open(output_file_ptr, O_WRONLY | O_CREAT, 0644);
    }
    else if (pipe_fds != NULL && pipe_write) {
        output_fd = pipe_fds[1];
        close(pipe_fds[0]);
    }
    if (input_fd != -1) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != -1) {
        // 这里也可以不适用dup，手动数据，处理后，再写入STDOUT也行，灵活性更高。
        // 当前的代码处理不了 cat < temp.txt | wc -l >
        // temp.txt，这种，读和写都是同一个文件的case
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }

    // exec
    execvp(token_ptrs[0], token_ptrs);
    perror("exec error");
    exit(1);
}

void run_cmd(char *buf)
{
    int pid1 = 0, pid2 = 0;
    int sub_process_num = 1;
    int pipe_filedes[2];
    int pipe_index = -1;
    memset(pipe_filedes, -1, sizeof(pipe_filedes));

    // get pipe '|' number
    for (int i = 0; buf[i]; i++) {
        if (buf[i] == '|') {
            sub_process_num++;
            pipe_index = i;
        };
    }
    // split cmd by \0
    if (pipe_index > 0) {
        buf[pipe_index] = '\0';
    }
    if (sub_process_num > 2) {
        fputs("just support one pipe", stderr);
        exit(1);
    }
    // create pipe
    if (sub_process_num == 2) {
        if (pipe(pipe_filedes) < 0) {
            perror("pipe");
            exit(1);
        }
    }

    // parent fork pid1
    pid1 = fork();
    if (pid1 < 0) {
        perror("fork pid1");
        exit(2);
    }
    // parent fork pid2
    if (pid1 > 0 && sub_process_num > 1) {
        pid2 = fork();
        if (pid2 < 0) {
            perror("fork pid2");
            exit(3);
        }
    }

    // pid1, when prent fork child1, pid1 is 0
    if (pid1 == 0) {
        exec_wrap(buf, pipe_filedes, 1, 0);
    }

    // pid2 (if exist), when parent fork child2, pid1 is't 0, and pid2 is 0
    if (sub_process_num > 1 && pid1 > 0 && pid2 == 0) {
        exec_wrap(buf + pipe_index + 1, pipe_filedes, 0, 1);
    }

    // parent, pid1 and pid2 aren't 0
    if (pid1 > 0 && (sub_process_num < 2 || pid2 > 0)) {
        if (pipe_filedes[0] != -1) {
            close(pipe_filedes[0]);
            close(pipe_filedes[1]);
        }
        for (int i = sub_process_num; i > 0; i--) {
            wait(NULL);
        }
    }
}

int main(int argc, char *argv[])
{
    char buf[1024];
    char exit_sentinel[] = "exit";
    while (1) {
        fputs("$ ", stdout);
        memset(buf, 0, sizeof(buf));
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            perror("fgets");
            exit(1);
        }
        if (strlen(buf) <= 1) continue;
        // delete '\n'
        buf[strlen(buf) - 1] = 0;
        if (strcmp(buf, exit_sentinel) == 0) {
            break;
        }
        run_cmd(buf);
    }
    return EXIT_SUCCESS;
}
