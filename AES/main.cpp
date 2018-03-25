#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <bitset>
#include "main_round.h"
#include "shift_rows.h"
#include "mix_column.h"
#include "make_roundkey.h"
#include "rounding.h"
#include "encode_base64.h"

using namespace std;

//16, 32 bit NR= 10,14
/* 필요는 없지만 혹시나 비트단위로 반나눠서 계산해야할때 사용함
int a={0},b={0},num{0};
bitset<4>bit1;
bit1=data[배열크기]>>4;
bitset<4>bit2;
bit2=data[배열크기];

a=bit1.to_ulong();
b=bit2.to_ulong();
*/

int main()
{
    uint8_t cipher[16]={0x00,0x44,0x88,0x33,
                        0x11,0x55,0x99,0x44,
                        0x22,0x66,0x11,0x55,
                        0x33,0x77,0x22,0x66};

    static const uint8_t sbox[256] = {
      //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
      0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
      0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
      0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
      0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
      0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
      0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
      0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
      0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
      0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
      0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
      0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
      0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
      0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
      0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
      0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
      0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

    static const uint8_t Rcon[11] = {
      0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };


    //****************************************************************************************************
    uint8_t startdata[16]{0};
    uint8_t data[16]{0};

home:
    cout << " >> Please enter the data you want to encrypt = ";
    cin >> startdata;
    for(int i=0,j=0,y=0; i<16; i++,j+=4)
    {
        if(j>13)
            j=0,y++;
        data[i]=startdata[j+y];
    }
    if(strlen((char*)startdata)!=16)
    {
        cout << "The length is too long" << endl;
        goto home;
    }
    system("clear");
    cout << " >> Plain Text = ";
    for(int i=0; i<4; i++)
    {
        printf("%c",data[i]);
        printf("%c",data[i+4]);
        printf("%c",data[i+8]);
        printf("%c",data[i+12]);
    }
    cout << endl;
    cout << " >> Plain Text = ";
    for(int i=0; i<4; i++)
    {
        printf("%02x",data[i]);
        printf("%02x",data[i+4]);
        printf("%02x",data[i+8]);
        printf("%02x",data[i+12]);
    }
    cout << endl;

    cout << " >> Cipher Key = ";
    for(int i=0; i<4; i++)
    {
        printf("%02x",cipher[i]);
        printf("%02x",cipher[i+4]);
        printf("%02x",cipher[i+8]);
        printf("%02x",cipher[i+12]);
    }
    cout << endl;
    //Fisrt XOR (data,cipher key)
    for(int i=0; i<16; i++)
    {
        data[i]=data[i]^cipher[i];
    }
    main_round(data,sbox);

    //AddRoundKey
    uint8_t Round1[16]{0};
    uint8_t Round2[16]{0};
    uint8_t Round3[16]{0};
    uint8_t Round4[16]{0};
    uint8_t Round5[16]{0};
    uint8_t Round6[16]{0};
    uint8_t Round7[16]{0};
    uint8_t Round8[16]{0};
    uint8_t Round9[16]{0};
    uint8_t Round10[16]{0};
    roundkey(cipher,Round1,Rcon[1],sbox);
    roundkey(Round1,Round2,Rcon[2],sbox);
    roundkey(Round2,Round3,Rcon[3],sbox);
    roundkey(Round3,Round4,Rcon[4],sbox);
    roundkey(Round4,Round5,Rcon[5],sbox);
    roundkey(Round5,Round6,Rcon[6],sbox);
    roundkey(Round6,Round7,Rcon[7],sbox);
    roundkey(Round7,Round8,Rcon[8],sbox);
    roundkey(Round8,Round9,Rcon[9],sbox);
    roundkey(Round9,Round10,Rcon[10],sbox);

    uint8_t data2[16]{0};
    uint8_t data3[16]{0};
    uint8_t data4[16]{0};
    uint8_t data5[16]{0};
    uint8_t data6[16]{0};
    uint8_t data7[16]{0};
    uint8_t data8[16]{0};
    uint8_t data9[16]{0};
    uint8_t ciphertext[16]{0};

    rounding(data,data2,Round1,sbox);
    rounding(data2,data3,Round2,sbox);
    rounding(data3,data4,Round3,sbox);
    rounding(data4,data5,Round4,sbox);
    rounding(data5,data6,Round5,sbox);
    rounding(data6,data7,Round6,sbox);
    rounding(data7,data8,Round7,sbox);
    rounding(data8,data9,Round8,sbox);

    for(int i=0; i<16; i++)
        ciphertext[i]=data9[i]^Round9[i];

    for(int i=0; i<16; i++)
        ciphertext[i]=sbox[ciphertext[i]];

    shift(ciphertext);

    for(int i=0; i<16; i++)
        ciphertext[i]=ciphertext[i]^Round10[i];

    //print
    cout << " >> AES Ciphertext = ";
    for(int i=0; i<4; i++)
    {
        printf("%02x",ciphertext[i]);
        printf("%02x",ciphertext[i+4]);
        printf("%02x",ciphertext[i+8]);
        printf("%02x",ciphertext[i+12]);
    }
    cout << endl << endl;


    cout << " >> AES Ciphertext = " << endl;
    for(int i =0; i<16; i++)
    {
        if(i%4==0)
            cout << endl;
        printf("  %02x ",ciphertext[i]);
    }
    cout << endl << endl;

    //base64(ciphertext);
    return 0;
}


