#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    int fd = open("./a.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    if (fd < 0) {
        fprintf(stderr, "open failed\n");
        exit(1);
    }
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        char *msg = "Child writes\n";
        write(fd, msg, strlen(msg));
        printf("Child (pid:%d) wrote to file\n", (int)getpid());
    }else {
        char *msg = "Parent writes\n";
        write(fd, msg, strlen(msg));
        printf("Parent (pid:%d) wrote to file\n", (int)getpid());
    }
    close(fd);
    return 0;
}

