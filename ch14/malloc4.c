#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(){
    int *data = malloc(100 * sizeof(int));
    int *a = &data[5];
    free(a);
    return 0;
}

