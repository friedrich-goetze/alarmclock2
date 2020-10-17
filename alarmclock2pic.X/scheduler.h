
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __MF_SCHEDULER__
#define	__MF_SCHEDULER__

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

void SCHEDULE_API_InitWaitTicks(void);
uint16_t SCHEDULE_API_WaitTicks(uint16_t ticks);

/** 
 * This must be called within any interrupt.
 * This function interrupts waiting.
 */
void SCHEDULE_API_OnInterrupt(void);

/**
 * Callback for task execution.
 * First parameter: Ticks since the last callback. If is 0xFF,
 * the duration is unknown.
 * 
 * Return: In how many ticks the task should be called again.
 * Special return values are:
 * 0x00 - immediately execute again after all other tasks were executed.
 * 0xFF - execute anytime
 */
void SCHEDULE_AddTask(uint16_t (*pTask)(uint16_t));

void SCHEDULE_Init(void);
void SCHEDULE_Run(void);

#endif	/* __MF_SCHEDULER__ */

