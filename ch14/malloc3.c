#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(){
    int *data = malloc(100 * sizeof(int));
    data[0] = 2;
    free(data);
    printf("data = %d\n", data[0]);
    return 0;
}

