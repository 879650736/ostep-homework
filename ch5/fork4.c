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
        char *myargs[3];
        myargs[0] = strdup("ls");
        myargs[1] = strdup("-l");
        myargs[2] = strdup(".");
        myargs[3] = NULL;
        execvp(myargs[0], myargs);
        printf("hello, I am child (pid:%d)\n", (int) getpid());

    }else {
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
            rc, wc, (int) getpid());

    }


}

