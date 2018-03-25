#ifndef SHIFT_ROWS_H
#define SHIFT_ROWS_H
void shift(uint8_t data[16])
{
    uint8_t temp{0};
    uint8_t temp2{0};
    temp=data[4];
    data[4]=data[5];
    data[5]=data[6];
    data[6]=data[7];
    data[7]=temp;

    temp=data[8];
    temp2=data[9];
    data[8]=data[10];
    data[9]=data[11];
    data[10]=temp;
    data[11]=temp2;

    temp = data[12];
    data[12]=data[15];
    data[15]=data[14];
    data[14]=data[13];
    data[13]=temp;
}
#endif // SHIFT_ROWS_H
