#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main(){
    int *data = malloc(100 * sizeof(int));
    data[100] = 0;
    
    return 0;
}

