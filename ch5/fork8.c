#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    
    // 创建管道
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // 创建第一个子进程（数据生产者）
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {    // 第一个子进程
        close(pipefd[0]); // 关闭读端

        // 将标准输出重定向到管道写端
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]); // 关闭原始写端

        printf("Hello from child1!\n"); // 此输出将进入管道
        fflush(stdout);                // 确保立即刷新缓冲区
        exit(EXIT_SUCCESS);
    }

    // 创建第二个子进程（数据消费者）
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {    // 第二个子进程
        close(pipefd[1]); // 关闭写端

        // 将标准输入重定向到管道读端
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); // 关闭原始读端

        char buffer[1024];
        // 从标准输入读取数据（来自管道）
        fgets(buffer, sizeof(buffer), stdin);
        printf("Child2 received: %s", buffer);
        exit(EXIT_SUCCESS);
    }

    // 父进程关闭所有管道描述符
    close(pipefd[0]);
    close(pipefd[1]);

    // 等待所有子进程结束
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    printf("Parent process done\n");
    return EXIT_SUCCESS;
}
