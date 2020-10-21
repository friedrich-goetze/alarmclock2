#include <xc.h>
#include <string.h>
#include <stdbool.h>
#include "scheduler.h"

#include "usart_util.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/tmr1.h"

#define TMR1_POLL ((uint16_t)4)
#define TMR1_MAXWAIT ((uint16_t)0xFFFF - TMR1_POLL)

volatile bool interrupted = false;

uint16_t __dummyTask(uint16_t x) {
    return 0;
}

uint16_t(*allTasks[])(uint16_t) = {
    __dummyTask,
    __dummyTask,
    __dummyTask,
    __dummyTask,
    __dummyTask,
    __dummyTask,
    __dummyTask,
    __dummyTask,
    __dummyTask
};

uint8_t nTasks = 0;

bool SCHEDULE_IsInterrupted(void);

void SCHEDULE_AddTask(uint16_t(*pTask)(uint16_t)) {
    allTasks[nTasks] = pTask;
    nTasks++;
}

void SCHEDULE_Init() {
    interrupted = false;
    TMR1_StartTimer();
}

void SCHEDULE_OnInterrupt() {
    interrupted = false;
}

void SCHEDULE_Run() {
    uint16_t(*pT)(uint16_t);
    uint8_t i;
    uint16_t waitSinceLast = (uint16_t) 0;
    uint16_t minWaitUntilNext;
    uint16_t now;
    uint16_t taskDuration;
    uint16_t waitUntilNext;

    while (1) {
        interrupted = false; // Catch only interrupts while tasks are running.
        minWaitUntilNext = (uint16_t) 0xFFFF;
        now = TMR1_ReadTimer();
        for (i = 0; i < nTasks; i++) {
            pT = allTasks[i];
            waitUntilNext = pT(waitSinceLast);
            if (waitUntilNext < minWaitUntilNext) {
                minWaitUntilNext = waitUntilNext;
            }
            pT++;
        }
        switch (minWaitUntilNext) {
            case (uint16_t) 0x0000:
                waitSinceLast = (uint16_t) 0;
                break;
            case (uint16_t) 0xFFFF:
                while (!EUSART1_is_tx_ready() || !EUSART1_is_tx_done());
                if (SCHEDULE_IsInterrupted()) {
                    waitSinceLast = 0;
                } else {
                    SLEEP();
                    NOP();
                    waitSinceLast = (uint16_t) 0xFFFF;
                }
                break;

            default:

                taskDuration = TMR1_ReadTimer() - now;
                if (taskDuration > minWaitUntilNext) {
                    minWaitUntilNext = 0;
                } else {
                    minWaitUntilNext -= taskDuration;
                }

                if (minWaitUntilNext <= TMR1_POLL) {
                    TMR1_StopTimer();
                    TMR1_WriteTimer((uint16_t) 0);
                    TMR1_StartTimer();
                    while (TMR1_ReadTimer() < minWaitUntilNext && !SCHEDULE_IsInterrupted());
                    waitSinceLast = TMR1_ReadTimer();
                } else {
                    // Prepare Timer to use its overflow interrupt to wake us up
                    uint16_t w = (minWaitUntilNext > TMR1_MAXWAIT) ? TMR1_MAXWAIT : minWaitUntilNext;
                    w--; // Wait one tick less too correct waiting
                    uint16_t period = (uint16_t) 0xFFFF - w;
                    // Fix in PIC-bug: SLEEP fails when transmitting USART data
                    TMR1_StopTimer();
                    TMR1_WriteTimer(period);
                    TMR1_StartTimer();
                    while (!EUSART1_is_tx_ready() || !EUSART1_is_tx_done());
                    if (!SCHEDULE_IsInterrupted()) {
                        SLEEP();
                        NOP();
                    }

                    waitSinceLast = TMR1_ReadTimer() - period;
                }
                
                waitSinceLast += taskDuration;
                break;
        }
    }
}

bool SCHEDULE_IsInterrupted(void) {
    if (interrupted) {
        interrupted = false;
        return true;
    }
    return false;
}