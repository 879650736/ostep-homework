#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    char buffer[1];

    // 创建管道
    if (pipe(pipefd)) {
        perror("pipe");
        exit(1);
    }

    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // 子进程关闭读端
        close(pipefd[0]);

        // 打印hello
        printf("hello\n");
        fflush(stdout);  // 确保输出立即刷新

        // 写入管道通知父进程
        write(pipefd[1], "A", 1);
        close(pipefd[1]);
    } else {
        // 父进程关闭写端
        close(pipefd[1]);

        // 阻塞等待子进程写入
        read(pipefd[0], buffer, 1);

        // 打印goodbye
        printf("goodbye\n");

        close(pipefd[0]);
    }
    return 0;
}
