#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<time.h>

#include "clz.h"


#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

#ifdef recursive
#define clz(x) clz2(x, 16)
#endif
static double diff_in_second(struct timespec start, struct timespec end);
int main ( int argc, char* argv[])
{
    FILE *p;

    struct timespec start = {0,0};
    struct timespec end = {0,0};
    uint32_t upper_bound = UINT16_MAX;
    clock_gettime(CLOCK_ID, &start);
    for(uint32_t i = 0; i < upper_bound; i++) {
        clz(i);
    }
    clock_gettime(CLOCK_ID, &end);
#ifdef binary
    p = fopen("binary.txt","a");
#elif iterate
    p = fopen("iterate.txt", "a");
#else
    p = fopen("recursive.txt", "a");
#endif
    fprintf(p,"%lf\n", diff_in_second(start, end));
    fclose(p);
    return 0;
}
static double diff_in_second(struct timespec start, struct timespec end)
{
    return (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
}
