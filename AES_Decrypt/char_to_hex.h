#ifndef CHAR_TO_HEX_H
#define CHAR_TO_HEX_H
void make_hex(char *str, uint8_t *data)
{
    sscanf((const char*)str,"%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX%2hhX",
           &data[0],&data[4],&data[8],&data[12],
           &data[1],&data[5],&data[9],&data[13],
           &data[2],&data[6],&data[10],&data[14],
           &data[3],&data[7],&data[11],&data[15]);
}
#endif // CHAR_TO_HEX_H
