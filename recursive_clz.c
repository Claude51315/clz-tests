#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
uint8_t recursive_clz(uint32_t x, uint32_t shifter);
#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0
int main ( int argc, char* argv[]){
    
    struct timespec start = {0,0};
    struct timespec end = {0,0};
    uint32_t upper_bound = UINT16_MAX << 5;
    clock_gettime(CLOCK_ID, &start);
    for(uint32_t i = 0; i < upper_bound; i++)
    {
        recursive_clz(i , 16);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("recursive duration: %lf\n", (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC);

   return 0;
}

uint8_t recursive_clz(uint32_t x, uint32_t shifter)
{
    /* if x's lowest bit == 0, return 1*/
    if(shifter == 0) return ((x+1) & 1) ;
    uint16_t upper = (x >> shifter);
    uint16_t lower = x & (0xFFFFFFFF >> shifter);
    return upper ? recursive_clz(upper , shifter >>1) : shifter + recursive_clz(lower, shifter>>1);
}


