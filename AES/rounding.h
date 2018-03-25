#ifndef ROUNDING_H
#define ROUNDING_H
#include "main_round.h"

void rounding(uint8_t data[16],uint8_t data2[16],uint8_t Round[16],const uint8_t sbox[256])
{
    for(int i=0; i<16; i++)
        data2[i]=data[i]^Round[i];

    main_round(data2,sbox);
}
#endif // ROUNDING_H
