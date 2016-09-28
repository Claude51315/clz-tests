#ifndef CLZ_H
#define CLZ_H

#include<stdint.h>
#ifndef recursive
uint8_t clz(uint32_t x);
#else
uint8_t clz2(uint32_t x, uint32_t shifter);
#endif
#endif
