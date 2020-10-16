#include "mcp23s17.h"
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include "usart_util.h"

void MCP_Send(uint8_t addr, uint8_t controlRegister, uint8_t mode, uint8_t* bytes, uint8_t len) {
    SPI1_Open(SPI1_DEFAULT);
    MCP_CS_LAT = 0;
    
    {
        char opAddr = (addr & 0b111) << 1;
        char opCode = 0b01000000 | opAddr | mode;
        SPI1_ExchangeByte(opCode);
    }
    
    SPI1_ExchangeByte(controlRegister);
    
    if(mode == MCP_WRITE) {
        SPI1_WriteBlock(bytes, len);
    } else {
        SPI1_ExchangeBlock(bytes, len);
    }
    
    MCP_CS_LAT = 1;
    SPI1_Close();
}