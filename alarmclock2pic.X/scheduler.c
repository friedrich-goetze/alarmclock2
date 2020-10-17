#include <xc.h>
#include <string.h>
#include <stdbool.h>
#include "scheduler.h"

#include "usart_util.h"
#include "mcc_generated_files/eusart1.h"

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

void SCHEDULE_AddTask(uint16_t(*pTask)(uint16_t)) {
    allTasks[nTasks] = pTask;
    nTasks++;
}

void SCHEDULE_Init() {
    interrupted = false;
    SCHEDULE_API_InitWaitTicks();
}

void SCHEDULE_OnInterrupt() {
    interrupted = false;
    SCHEDULE_API_OnInterrupt();
}

void SCHEDULE_Run() {
    uint16_t(*pT)(uint16_t);
    uint8_t i;
    uint16_t waitSinceLast = (uint16_t) 0;
    uint16_t minWaitUntilNext;
    uint16_t waitUntilNext;

    while (1) {
        while (!EUSART1_is_tx_ready());
        EUSART1_Write('t');
        minWaitUntilNext = (uint16_t) 0xFFFF;
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
                if (interrupted) {
                    waitSinceLast = 0;
                } else {
                    SLEEP();
                    NOP();
                    waitSinceLast = (uint16_t) 0xFFFF;
                }

                break;
            default:
                waitSinceLast = SCHEDULE_API_WaitTicks(minWaitUntilNext);
                break;
        }
        interrupted = false;
    }
}

