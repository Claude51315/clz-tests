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
static inline void get_cycles(unsigned *high,unsigned *low)
{
    asm volatile ("CPUID\n\t"
                  "RDTSC\n\t"
                  "mov %%edx, %0\n\t"
                  "movl %%eax, %1\n\t": "=r" (*high), "=r" (*low)::"%rax","%rbx","%rcx","%rdx"
                 );
}

static inline void get_cycles_end(unsigned *high,unsigned *low)
{

    asm volatile("RDTSCP\n\t"
                 "mov %%edx, %0\n\t"
                 "mov %%eax, %1\n\t"
                 "CPUID\n\t": "=r" (*high), "=r" (*low)::"%rax","%rbx","%rcx","%rdx"
                );
}
static inline uint64_t diff_in_cycles(unsigned high1,unsigned low1,unsigned high2,unsigned low2)
{
    uint64_t start,end;
    start = ( ((uint64_t)high1 << 32) | low1 );
    end = ( ((uint64_t)high2 << 32) | low2 );
    return end-start;
}


static double diff_in_second(struct timespec start, struct timespec end);
static double diff_in_nano_second(struct timespec start, struct timespec end);
int main ( int argc, char* argv[])
{
    FILE *p;
    unsigned time_high1, time_high2, time_low1, time_low2;
    struct timespec start = {0,0};
    struct timespec end = {0,0};
    uint32_t upper_bound = UINT16_MAX;
    //clock_gettime(CLOCK_ID, &start);
    for(uint32_t i = 0; i < upper_bound; i++) {
        //clock_gettime(CLOCK_ID, &start);
        get_cycles(&time_high1, &time_low1);
        clz(i);
        get_cycles_end(&time_high2, &time_low2);
        //clock_gettime(CLOCK_ID, &end);
#ifdef binary
        p = fopen("binary.txt","a");
#elif iterate
        p = fopen("iterate.txt", "a");
#elif byte_shift
        p = fopen("byteshift.txt", "a");
#else
        p = fopen("recursive.txt", "a");
#endif
        //fprintf(p,"%lf\n", diff_in_nano_second(start, end));
        fprintf(p,"%lu\n", diff_in_cycles(time_high1, time_low1, time_high2, time_low2));
        fclose(p);

    }
    //clock_gettime(CLOCK_ID, &end);
    return 0;
}
static double diff_in_second(struct timespec start, struct timespec end)
{
    return (double) (end.tv_sec - start.tv_sec)+(end.tv_nsec - start.tv_nsec)/ONE_SEC;
}
static double diff_in_nano_second(struct timespec start, struct timespec end)
{
    return (double)(end.tv_nsec - start.tv_nsec);
}
