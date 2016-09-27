#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
uint8_t binary_search_clz(uint32_t x);
#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0
int main ( int argc, char* argv[]){
    
    struct timespec start = {0,0};
    struct timespec end = {0,0};
    uint32_t upper_bound = UINT16_MAX;
    clock_gettime(CLOCK_ID, &start);
    for(uint32_t i = 0; i < upper_bound; i++)
    {
        binary_search_clz(i);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("binary search,%lf\n", (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC);  
    
    return 0;
}
uint8_t binary_search_clz(uint32_t x)
{
    if(x == 0 ) return 32;
    int n = 0;
    if (x <= 0x0000FFFF) { n += 16; x <<= 16; }
    if (x <= 0x00FFFFFF) { n += 8; x <<= 8; }
    if (x <= 0x0FFFFFFF) { n += 4; x <<= 4; }
    if (x <= 0x3FFFFFFF) { n += 2; x <<= 2; }
    if (x <= 0x7FFFFFFF) { n += 1; x <<= 1; }
    return n;
}
