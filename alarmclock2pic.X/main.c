#include <stdio.h>
#include <string.h>
#include "mcc_generated_files/mcc.h"
#include "scheduler.h"
#include "lcd_driver.h"
#include "usart_util.h"
#include "mcp23s17.h"
#include "buttons.h"
#include "ui.h"
#include "alarm.h"
#include "persistance.h"

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
    ALARM_Init();
    UI_Init();
    SCHEDULE_Init();
    PERSISTANCE_Init();


    //    SCHEDULE_AddTask(LCD_Task);
    SCHEDULE_AddTask(BTN_Update);
    SCHEDULE_AddTask(ALARM_Update);
    SCHEDULE_AddTask(UI_Update);
    SCHEDULE_AddTask(LCD_Task);
    SCHEDULE_AddTask(PERSISTANCE_Update);
    SCHEDULE_Run();
}
/**
 End of File
 */