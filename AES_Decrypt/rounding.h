#ifndef ROUNDING_H
#define ROUNDING_H

void rounding(uint8_t data[16], const uint8_t rsbox[256])
{
    for(int i=0; i<16; i++)
        data[i]=rsbox[data[i]];
}
#endif // ROUNDING_H
