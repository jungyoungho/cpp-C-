#ifndef MAIN_ROUND_H
#define MAIN_ROUND_H
#include "mix_column.h"
#include "shift_rows.h"
#include <bitset>

using namespace std;

void main_round(uint8_t data[16], const uint8_t sbox[256])
{
    //Use S-box
    for(int i=0; i<16; i++)
    {
        data[i]=sbox[data[i]];
    }
    //Shift Rows
    shift(data);

    //Mix Columns
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

#endif // MAIN_ROUND_H
