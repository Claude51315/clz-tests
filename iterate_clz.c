#include "clz.h"
uint8_t clz(uint32_t x)
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
