#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    #pragma omp parallel 
    {
        printf("I am a parallel region\n");
    }
    return 0;
}