#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "scheduler.h"
#include "lcd_driver.h"
#include "usart_util.h"
#include "mcp23s17.h"
#include "buttons.h"
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
    
    printf("Hello!\n");
    
//    LCD_Init();
    LCD_Init();
    BTN_Init();
    LCD_EnableBgLed(true);
    
    char* p = LCD_TakeBuffer();
    memcpy(p + LCD_COLS, "abcdefghijklmnop", 16);
    memcpy(p, "ABCDEFGJHIKLMNOP", 16);
    LCD_PushBuffer();
    
    LCD_ShowCursor(0, 6, LCD_CURSOR_BLINKING);
    
    
    p = LCD_TakeBuffer();
    memcpy(p + LCD_COLS, "1234567890987654", 16);
    memcpy(p, "0987654312345678", 16);
    LCD_PushBuffer();
    
    
    SCHEDULE_Init();
        
//    SCHEDULE_AddTask(LCD_Task);
    SCHEDULE_AddTask(BTN_Update);
    SCHEDULE_AddTask(LCD_Task);

    SCHEDULE_Run();
}
/**
 End of File
 */