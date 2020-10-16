#ifndef USART_UTIL_H
#define	USART_UTIL_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void printHex(uint8_t b);
void printBits(uint8_t b);
void printHexBuf(const uint8_t* pBuf, uint8_t len);
void printBitBuf(const uint8_t* pBuf, uint8_t len);

#endif	/* XC_HEADER_TEMPLATE_H */

