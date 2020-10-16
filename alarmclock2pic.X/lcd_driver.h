// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_DRIVER_H
#define	LCD_DRIVER_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "scheduler.h"

#define LCD_ROWS 2
#define LCD_COLS 16

#define LCD_CURSOR_OFF 0
#define LCD_CURSOR_SOLID 1
#define LCD_CURSOR_BLINKING 1

typedef struct LCD_Buffers {
    char rows[LCD_ROWS][LCD_COLS + 1];
} LCD_Buffer;

void LCD_Init();
uint16_t LCD_Task(uint16_t);

LCD_Buffer* LCD_TakeBuffer();
void LCD_PushBuffer();
void LCD_ShowCursor(uint8_t row, uint8_t col, uint8_t mode);
void LCD_EnableBgLed(bool enable);
void LCD_Clear();

#endif	/* XC_HEADER_TEMPLATE_H */

