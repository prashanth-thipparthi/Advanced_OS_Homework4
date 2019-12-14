#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
    char *array;
    int bytes = 40000000; // Allocate 10 MB of memory for this program

    array = (char *) malloc(bytes); 
    for (int i = 0; i < bytes; ++i) {
        array[i] = 1;
    }   

    printf("mem_test allocated %d bytes of memory\n", bytes);

    sleep(10);

    free(array);
} 
