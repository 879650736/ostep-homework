#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // 子进程关闭标准输出
        close(STDOUT_FILENO);  // 关闭文件描述符1

        // 尝试打印
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    } else {
        // 父进程等待子进程
        int wc = waitpid(rc, NULL, 0);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }

    return 0;
}
