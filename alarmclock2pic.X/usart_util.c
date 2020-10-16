#include "usart_util.h"
#include "mcc_generated_files/eusart1.h"

char buf[32];

char toHexDigit(uint8_t x) {
    x = x & 0xF;
    return (x < 10) ? '0' + x : 'a' + x - 10;
}

void printHex(uint8_t b) {
    buf[0] = toHexDigit(b >> 4);
    buf[1] = toHexDigit(b);
    buf[2] = 0;
    printf(buf);
}

void printBits(uint8_t b) {
    uint8_t m = 0x1 << 7;
    for (uint8_t i = 0; i < 8; i++) {
        buf[i] = (b & m) ? '1' : '0';
        m = m >> 1;
    }
    buf[8] = 0;
    printf(buf);
}

void printHexBuf(const uint8_t* pBuf, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        printHex(*pBuf);
        if(i != len-1) {
            printf(" ");
        }
        pBuf++;
    }
}
void printBitBuf(const uint8_t* pBuf, uint8_t len) {
    for (uint8_t i = 0; i < len; i++) {
        printBits(*pBuf);
        if(i != len-1) {
            printf(" ");
        }
        pBuf++;
    }
}