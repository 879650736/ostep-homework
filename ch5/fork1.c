#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]){
    int x = 100;
    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        x=1;
        printf("x:%d\n",x);
    }else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
            rc, wc, (int) getpid());
        x=2;
        printf("x:%d\n",x);
    }


}

