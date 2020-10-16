#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "scheduler.h"
#include "lcd_driver.h"
#include "usart_util.h"
#include "mcp23s17.h"

uint8_t x = 0;

uint16_t task(uint16_t duration) {
        x++;
        printf("oo %u -> %u\n", x, duration);
    return (uint16_t)0x7FFF;
}
/*
                         Main application
 */
void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
//    LCD_Init();
    LCD_Init();
    LCD_EnableBgLed(true);
    
    LCD_Buffer* p = LCD_TakeBuffer();
    strcpy(p->rows[0], "Hello world");
    strcpy(p->rows[1], "Foo Bar");
    LCD_PushBuffer();
    
    LCD_ShowCursor(0, 6, LCD_CURSOR_BLINKING);
    
    SCHEDULE_Init();
        
//    SCHEDULE_AddTask(LCD_Task);
    SCHEDULE_AddTask(LCD_Task);

    SCHEDULE_Run();
}
/**
 End of File
 */