#include "clz.h"
uint8_t clz2(uint32_t x, uint32_t shifter)
{
    /* if x's lowest bit == 0, return 1*/
    if(shifter == 0) return ((x+1) & 1) ;
    uint16_t upper = (x >> shifter);
    /* mask out the lower-half bits*/
    uint16_t lower = x & (0xFFFFFFFF >> (32-shifter));
    return upper ? clz2(upper , shifter >>1) : shifter + clz2(lower, shifter>>1);
}


