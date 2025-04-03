#define _GNU_SOURCE  // 必须放在最顶部！
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <stdlib.h>  // 添加 exit 声明

#define ITERATIONS 100000

void set_affinity(int cpu) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu, &set);
    sched_setaffinity(0, sizeof(set), &set);
}

int main() {
    int pipe1[2], pipe2[2];
    char buf[1];
    struct timeval start, end;

    pipe(pipe1);
    pipe(pipe2);
    pid_t pid = fork();

    if (pid == 0) { // 子进程
        set_affinity(0);
        for (int i = 0; i < ITERATIONS; i++) {
            read(pipe1[0], buf, 1);
            write(pipe2[1], "a", 1);
        }
        return 0;
    } else { // 父进程
        set_affinity(0);
        gettimeofday(&start, NULL);
        for (int i = 0; i < ITERATIONS; i++) {
            write(pipe1[1], "a", 1);
            read(pipe2[0], buf, 1);
        }
        gettimeofday(&end, NULL);

        long total = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        double per_switch = (double)total / (2 * ITERATIONS);
        printf("Context switch cost: %.2f us\n", per_switch);

        wait(NULL);
    }
    return 0;
}
