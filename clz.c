#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
uint8_t recursive_clz(uint32_t x, uint32_t shifter);

int main (){
    uint32_t a = 0x00000000;
    uint8_t ans = recursive_clz(a, 16);
    printf("%u\n", ans);
    return 0;
}

uint8_t recursive_clz(uint32_t x, uint32_t shifter)
{
    /* if x's lowest bit == 0, return 0*/
    if(shifter == 0) return ((x+1) & 1) ;
    uint16_t upper = (x >> shifter);
    uint16_t lower = x & (0xFFFFFFFF >> shifter);
    return upper>0 ? recursive_clz(upper , shifter>>1) : shifter + recursive_clz(lower, shifter>>1);
}
