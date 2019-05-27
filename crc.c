// CRC16-XMODEM（x16+x12+x5+1)的查表法实现
// 结果验证参照 http://www.ip33.com/crc.html
#include <stdio.h>

unsigned short crc16_table[256];

// 生成256个字符的CRC码
void make_crc16_table()
{
    unsigned short crc16;
    unsigned short poly = 0x1021; 
    unsigned short i, j, k;
    for (i = 0; i < 256; ++i) {
        crc16 = i << 8;
        for ( j = 0; j < 8; ++j) {
            if (crc16 & 0x8000) {
            // 寄存器首位为1，左移一位再与生成多项式异或
                crc16 = (crc16 << 1) ^ poly;
            } else {
            // 寄存器首位为0，仅左移一位
                crc16 <<= 1;
            }
        }
        crc16_table[i] = crc16;
    }
}

unsigned short recalculate_crc16(unsigned short crc16, unsigned char *data, int len)
{
    while (len-- > 0) {
        crc16 = (crc16 << 8) ^ crc16_table[((crc16 >> 8) ^ (*data++)) & 0xff];
    }
    return crc16;
}

int main()
{
    make_crc16_table();
#if 0
    printf("crc16_table[256] = {");
    for (int i = 0; i < 256; ++i) {
        if (i % 5 == 0)
            printf("\n\t");
        printf("0x%04x",crc16_table[i]);
        if (i != 255)
            printf(", ");
    }
    printf("\n}\n");
#endif
    unsigned char data[] = "\x11\x22\x33\x44";
    unsigned short crc16 = 0;
    crc16 = recalculate_crc16(crc16, data, 4);
    printf("crc16 = 0x%04x\n", crc16);
}