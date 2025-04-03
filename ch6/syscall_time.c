#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

#define ITERATIONS 1000000

int main() {
    struct timeval start, end;
    int fd = open("/dev/null", O_RDONLY);
    char buf[1];
    volatile int j;

    // 测量空循环时间
    gettimeofday(&start, NULL);
    for (int i = 0; i < ITERATIONS; i++) {
        j = i;
    }
    gettimeofday(&end, NULL);
    long empty_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    
    // 测量系统调用时间
    gettimeofday(&start, NULL);
    for (int i = 0; i < ITERATIONS; i++) {
        read(fd, buf, 0);
    }
    gettimeofday(&end, NULL);
    long syscall_time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);

    double avg = (double)(syscall_time - empty_time) / ITERATIONS;
    printf("System call cost: %.2f us\n", avg);

    close(fd);
    return 0;
}
