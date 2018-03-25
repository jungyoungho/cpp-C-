#ifndef MAKE_ROUNDKEY_H
#define MAKE_ROUNDKEY_H

void roundkey(uint8_t pre_round[16], uint8_t next_Round[16], uint8_t Rcon, const uint8_t sbox[256])
{
    next_Round[0]=pre_round[7];
    next_Round[4]=pre_round[11];
    next_Round[8]=pre_round[15];
    next_Round[12]=pre_round[3];

    for(int i=0; i<16; i+=4)
    {
        next_Round[i]=sbox[next_Round[i]];
    }
    next_Round[0]=next_Round[0]^Rcon;
    for(int i=0; i<16; i+=4)
    {
        next_Round[i]=next_Round[i]^pre_round[i];
        next_Round[i+1]=next_Round[i]^pre_round[i+1];
        next_Round[i+2]=next_Round[i+1]^pre_round[i+2];
        next_Round[i+3]=next_Round[i+2]^pre_round[i+3];
    }
}
#endif // MAKE_ROUNDKEY_H
