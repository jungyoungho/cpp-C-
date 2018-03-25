#ifndef RIJNDAEL_H
#define RIJNDAEL_H
#include <bitset>
#include "shift_rows.h"
#include "rounding.h"
#include "mix_column.h"

using namespace std;

void routine(uint8_t data[16], uint8_t Round[16], const uint8_t rsbox[256])
{
    shift(data);
    rounding(data,rsbox);

    for(int i=0; i<16; i++)
        data[i]=data[i]^Round[i];

    bitset<8>bit1;
    bitset<8>bit2;
    bitset<8>bit3;
    bitset<8>bit4;
    uint8_t mixsum[16]{0};
    for(int j=0,i=0; i<4; i++,j++)
    {
        bit1=data[i];
        int a=bit1.to_ulong();
        bit2=data[i+4];
        int b=bit2.to_ulong();
        bit3=data[i+8];
        int c=bit3.to_ulong();
        bit4=data[i+12];
        int d=bit4.to_ulong();
        switch (i)
        {
            case 0:
                mix_column(a,b,c,d,mixsum,j);
            break;
            case 1:
                mix_column(a,b,c,d,mixsum,j);
            break;
            case 2:
                mix_column(a,b,c,d,mixsum,j);
            break;
            case 3:
                mix_column(a,b,c,d,mixsum,j);
            break;
        }
    }
    memcpy(data,mixsum,16);
}
#endif // RIJNDAEL_H
