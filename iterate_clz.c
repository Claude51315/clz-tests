#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>
uint8_t iterate_clz(uint32_t x);
#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0
int main ( int argc, char* argv[])
{

    struct timespec start = {0,0};
    struct timespec end = {0,0};
    uint32_t upper_bound = UINT16_MAX;
    FILE *p ;

    clock_gettime(CLOCK_ID, &start);
    for(uint32_t i = 0; i < upper_bound; i++) {
        iterate_clz(i);
    }
    clock_gettime(CLOCK_ID, &end);
    p = fopen("origin_data.txt", "a");
    fprintf(p,"iterate %lf\n", (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC);
    fclose(p);
    return 0;
}
uint8_t iterate_clz(uint32_t x)
{
    int n = 32 , shifter = 16 ;
    do {
        uint32_t y = x >> shifter;
        if(y) {
            n -= shifter;
            x = y;
        }
        shifter >>=1;
    } while(shifter);
    return (n-x);
}
