#ifndef MCP23S17_H
#define	MCP23S17_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>

/* CONFIG */
#define MCP_CS_LAT LATBbits.LATB5

/* REGISTER address of A register, B is + 1.*/
#define MCP_IODIR   0x00
#define MCP_IPOL    0x02
#define MCP_GPINTEN 0x04
#define MCP_DEFVAL  0x06
#define MCP_INTCON  0x08
#define MCP_IOCON   0x0A
#define MCP_GPPU    0x0C
#define MCP_INTF    0x0E
#define MCP_INTCAP  0x10
#define MCP_GPIO    0x12
#define MCP_OLAT    0x14

/* MODE */
#define MCP_WRITE 0x00
#define MCP_READ 0x01

void MCP_Send(uint8_t addr, uint8_t controlRegister, uint8_t mode, uint8_t* bytes, uint8_t len);

#endif	/* XC_HEADER_TEMPLATE_H */

