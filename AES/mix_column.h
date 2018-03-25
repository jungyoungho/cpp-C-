#ifndef MIX_COLUMN_H
#define MIX_COLUMN_H
void cal(int a, int b,int c, int d,uint8_t *mixsum,int j)
{
    if(a*2>255)
    {
        a=(2*a-256)^0x1b;
    }
    else
    {
        a=2*a;
    }
    if(b*2>255)
    {
        b=(2*b-256)^0x1b^b;
    }
    else
    {
        b=b*2^b;
    }
    mixsum[j]=a^b^c^d;
}
void mix_column(int a, int b, int c, int d, uint8_t *mixsum, int j)
{
    int temp_a=a;
    int temp_b=b;
    int temp_c=c;
    int temp_d=d;
    //2 3 1 1
    cal(a,b,c,d,mixsum,j);
    //1 2 3 1
    a=temp_a,b=temp_b,c=temp_c,d=temp_d;
    cal(b,c,a,d,mixsum,j+4);
    //1 1 2 3
    a=temp_a,b=temp_b,c=temp_c,d=temp_d;
    cal(c,d,a,b,mixsum,j+8);
    //3 1 1 2
    a=temp_a,b=temp_b,c=temp_c,d=temp_d;
    cal(d,a,b,c,mixsum,j+12);
}
#endif // MIX_COLUMN_H
