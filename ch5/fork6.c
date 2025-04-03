#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main (int argc, char *argv[]){

    int rc = fork();
    if (rc < 0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0){
        int wc = 0;
        //int wc = waitpid();
        printf("hello, I am child (wc:%d) (pid:%d)\n", wc, (int) getpid());

    }else {
        //int wc = 0;
        int wc = waitpid(rc, NULL, 0);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
            rc, wc, (int) getpid());

    }


}

