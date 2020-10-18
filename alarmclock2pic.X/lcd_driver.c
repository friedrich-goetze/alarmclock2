/*
 * File:   lcd_driver.c
 * Author: fgoetze
 *
 * Created on September 27, 2020, 2:29 PM
 */


#include <xc.h>
#include <stdbool.h>
#include <string.h>
#include "lcd_driver.h"
#include "mcp23s17.h"
#include "mcc_generated_files/device_config.h"
#include "usart_util.h"

#define LCD_N_COMMANDS 128

#define LCD_INSTRUCTION_REG 0
#define LCD_DATA_REGISTER 0b1
#define LCD_MODE_WRITE 0
#define LCD_MODE_READ 0b10

#define LCD_CMD_CLEAR 0
#define LCD_CMD_RETURN_HOME 1
#define LCD_CMD_ENTRY_MODE_SET 2
#define LCD_CMD_ENTRY_MODE_INCREMENT 0b10
#define LCD_CMD_ENTRY_MODE_DECREMENT 0
#define LCD_CMD_ENTRY_MODE_ACOMPANIES_DISP_SHIFT 0b1
#define LCD_CMD_DISPLAY_CTRL 3
#define LCD_CMD_DISPLAY_CTRL_DISP_ON 0b100
#define LCD_CMD_DISPLAY_CTRL_CURSOR_ON 0b10
#define LCD_CMD_DISPLAY_CTRL_BLINK_ON 0b1
#define LCD_CMD_CURSOR_DISP_SHIFT 4
#define LCD_CMD_CURSOR_DISP_SHIFT_DISP_SHIFT 0b100
#define LCD_CMD_CURSOR_DISP_SHIFT_CURSOR_SHIFT 0
#define LCD_CMD_CURSOR_DISP_SHIFT_RIGHT 0b10
#define LCD_CMD_CURSOR_DISP_SHIFT_LEFT 0
#define LCD_CMD_FUNC_SET 5
#define LCD_CMD_FUNC_SET_8BITS 0b10000
#define LCD_CMD_FUNC_SET_4BITS 0
#define LCD_CMD_FUNC_SET_TWO_LINES 0b1000
#define LCD_CMD_FUNC_SET_ONE_LINE 0
#define LCD_CMD_FUNC_SET_5x10_DOTS 0b100
#define LCD_CMD_FUNC_SET_5x8_DOTS 0
#define LCD_CMD_SET_CGRAM_ADDR 6
#define LCD_CMD_SET_DDRAM_ADDR 7
#define LCD_CMD_WRITE_DATA 8
#define LCD_CMD_INIT_OP 9
#define LCD_N_CMDDEFS 10

typedef struct LCD_CmdDefs {
    uint8_t bitmask;
    uint16_t minTicks;
    bool isNoop : 1;
    bool isDataReg : 1;
} LCD_CmdDef;

typedef struct LCD_Commands {
    uint8_t cmdId;
    uint8_t data;
} LCD_Command;

typedef struct LSC_MCP_Buffers {
    uint8_t data;
    bool dataRegister : 1; // Instruction Reg otherwise
    bool read : 1;
    bool enable : 1;
    bool enableBg : 1;
} LCD_MCP;

const LCD_CmdDef cmdDefs[] = {
    { // 0 CLEAR
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b1,
        .minTicks = (uint16_t) 50
    },
    { // 1 RETURN HOME
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b10,
        .minTicks = (uint16_t) 50
    },
    { // 2 ENTRY MODE SET
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b100,
        .minTicks = (uint16_t) 2
    },
    { // 3 DISPLAY CTRL
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b1000,
        .minTicks = (uint16_t) 2
    },
    { // 4 CURSOR_DISP_SHIFT
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b10000,
        .minTicks = (uint16_t) 2
    },
    { // 5 FUNC SET
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b100000,
        .minTicks = (uint16_t) 2550
    },
    { // 6 SET CGRAM ADDR
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b1000000,
        .minTicks = (uint16_t) 2
    },
    { // 7 SET DDRAM ADDR
        .isNoop = false,
        .isDataReg = false,
        .bitmask = 0b10000000,
        .minTicks = (uint16_t) 2
    },
    { // 8 WRITE DATA
        .isNoop = false,
        .isDataReg = true,
        .bitmask = 0,
        .minTicks = (uint16_t) 2
    },
    { // 9 INIT
        .isNoop = true,
        .isDataReg = false,
        .bitmask = 0,
        .minTicks = (uint16_t) 0x7fff
    }
};

char chBuf[LCD_TOTAL_CHARS];
char lastChBuf[LCD_TOTAL_CHARS];

LCD_Command cmds[LCD_N_COMMANDS];
uint8_t curCmd = 0;
uint8_t lastCmd = 0;

LCD_MCP mcpBuf;

uint8_t mcpTransfer[2];

uint16_t ticksUntilNextCmd = 0;
uint16_t initTicksUntilNextCmd = 0;

uint8_t cursorMode = LCD_CURSOR_OFF;

void LCD_PushCommand(uint8_t cmd, uint8_t data);
void LCD_ClearCommands(void);
void LCD_ClockCommand(void);
void LCD_SendMcpBuf(void);

void LCD_Init() {
    memset(chBuf, ' ', sizeof (chBuf));
    memset(lastChBuf, ' ', sizeof (lastChBuf));
    memset(cmds, 0, sizeof (cmds));

    cursorMode = LCD_CURSOR_OFF;

    // Both output
    mcpTransfer[0] = 0;
    mcpTransfer[1] = 0;
    MCP_Send(0, MCP_OLAT, MCP_WRITE, mcpTransfer, 2);
    MCP_Send(0, MCP_IODIR, MCP_WRITE, mcpTransfer, 2);

    // Init mcp data and send it
    mcpBuf.data = 0;
    mcpBuf.enableBg = false;
    mcpBuf.enable = false;
    mcpBuf.dataRegister = false;
    mcpBuf.read = false;
    LCD_SendMcpBuf();

    ticksUntilNextCmd = 0;
    initTicksUntilNextCmd = 0;
    curCmd = 0;
    lastCmd = 0;

    LCD_PushCommand(LCD_CMD_INIT_OP, 0);
    LCD_PushCommand(
            LCD_CMD_FUNC_SET,
            LCD_CMD_FUNC_SET_8BITS
            | LCD_CMD_FUNC_SET_TWO_LINES
            | LCD_CMD_FUNC_SET_5x10_DOTS
            );
    LCD_PushCommand(
            LCD_CMD_DISPLAY_CTRL,
            LCD_CMD_DISPLAY_CTRL_DISP_ON
            );
    LCD_PushCommand(
            LCD_CMD_ENTRY_MODE_SET,
            LCD_CMD_ENTRY_MODE_INCREMENT
            );

    LCD_PushCommand(
            LCD_CMD_CLEAR,
            0);
}

uint8_t x = 0;

uint16_t LCD_Task(uint16_t durationSinceLast) {
    // check if is busy
    if (ticksUntilNextCmd > 0) {
        if (durationSinceLast == (uint16_t) 0xFFFF) {
            // after unknown period of waiting, re-wait for current command to finish
            ticksUntilNextCmd = initTicksUntilNextCmd;
        } else if (durationSinceLast >= ticksUntilNextCmd) {
            ticksUntilNextCmd = 0;
        } else {
            ticksUntilNextCmd -= durationSinceLast;
        }
        return ticksUntilNextCmd;
    }

    if (curCmd == lastCmd) {
        return (uint16_t) 0xFFFF;
    }

    // Get all command data
    LCD_Command* pCurCmd = &cmds[curCmd];
    const LCD_CmdDef* pCmdDef = &cmdDefs[pCurCmd->cmdId];

    // execute command
    if (!pCmdDef->isNoop) {
        mcpBuf.read = false;
        mcpBuf.dataRegister = pCmdDef->isDataReg;
        mcpBuf.data = pCmdDef->bitmask | pCurCmd->data;
        LCD_ClockCommand();
    }

    // Setup wait time
    initTicksUntilNextCmd = pCmdDef->minTicks;
    ticksUntilNextCmd = initTicksUntilNextCmd;

    // goto next cmd
    curCmd++;
    if (curCmd >= LCD_N_COMMANDS) {
        curCmd = 0;
    }

    // Call as soon as possible
    return ticksUntilNextCmd;
}

char* LCD_TakeBuffer() {
    return chBuf;
}

void LCD_PushBuffer() {
    // Cleanup existing commands
    LCD_ClearCommands();

    uint8_t ddStartAddr = 0;
    uint8_t j;
    uint8_t addr = 0;
    bool sendAddr = true;

    for (uint8_t i = 0; i < LCD_TOTAL_CHARS; i++) {
        if (lastChBuf[i] == chBuf[i]) {
            sendAddr = true;
            continue;
        }
        if (sendAddr) {
            addr = 0;
            j = i;
            while (j >= LCD_COLS) {
                addr += 0x40;
                j -= LCD_COLS;
            }
            addr += j; // Remainder
            LCD_PushCommand(LCD_CMD_SET_DDRAM_ADDR, addr);
            sendAddr = false;
        }
        LCD_PushCommand(LCD_CMD_WRITE_DATA, chBuf[i]);
    }

    memcpy(lastChBuf, chBuf, sizeof (chBuf));
    memset(chBuf, ' ', sizeof (chBuf));
}

void LCD_ShowCursor(uint8_t row, uint8_t col, uint8_t mode) {
    if (mode) {
        if (row >= LCD_ROWS) {
            row = LCD_ROWS - 1;
        }
        if (col >= LCD_COLS) {
            col = LCD_COLS - 1;
        }
        LCD_PushCommand(LCD_CMD_SET_DDRAM_ADDR, row * 0x40 + col);
    }

    if (mode != cursorMode) {
        uint8_t m = LCD_CMD_DISPLAY_CTRL_DISP_ON;
        if (mode) {
            m |= LCD_CMD_DISPLAY_CTRL_CURSOR_ON;
            if (mode == LCD_CURSOR_BLINKING) {
                m |= LCD_CMD_DISPLAY_CTRL_BLINK_ON;
            }
        }

        LCD_PushCommand(LCD_CMD_DISPLAY_CTRL, m);
    }

    cursorMode = mode;
}

void LCD_EnableBgLed(bool enable) {
    if (mcpBuf.enableBg != enable) {
        mcpBuf.enableBg = enable;
        LCD_SendMcpBuf();
    }
}

void LCD_Clear() {
    LCD_PushCommand(LCD_CMD_CLEAR, 0);
}

void LCD_PushCommand(uint8_t cmd, uint8_t data) {
    LCD_Command* pCmd = &cmds[lastCmd];
    LCD_CmdDef def = cmdDefs[cmd];

    // Defaults
    pCmd->cmdId = cmd;
    pCmd->data = data;

    lastCmd++;
    if (lastCmd >= LCD_N_COMMANDS) {
        lastCmd = 0;
    }
}

void LCD_ClockCommand() {
    mcpBuf.enable = false;
    LCD_SendMcpBuf();
    mcpBuf.enable = true;
    LCD_SendMcpBuf();
    mcpBuf.enable = false;
    LCD_SendMcpBuf();
}

void LCD_SendMcpBuf() {
    MCP_Send(0, MCP_OLAT, MCP_WRITE, (uint8_t*) & mcpBuf, 2);
}

void LCD_ClearCommands() {
    LCD_Command* p;
    while (curCmd != lastCmd) {
        p = &cmds[curCmd];
        if (p->cmdId != LCD_CMD_WRITE_DATA && p->cmdId != LCD_CMD_SET_DDRAM_ADDR) {
            break;
        }
        curCmd++;
        if (curCmd >= LCD_N_COMMANDS) {
            curCmd = 0;
        }
    }
}