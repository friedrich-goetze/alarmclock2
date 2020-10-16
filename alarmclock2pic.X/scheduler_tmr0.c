#include <xc.h>
#include "scheduler.h"
#include "mcc_generated_files/tmr1.h"

#define TMR1_POLL ((uint16_t)4)
#define TMR1_MAXWAIT ((uint16_t)0xFFFF - TMR1_POLL)

void TMR_Interrupt() {
}

void SCHEDULE_API_InitWaitTicks() {
    TMR1_SetInterruptHandler(TMR_Interrupt);
    TMR1_StopTimer();
}

uint16_t SCHEDULE_API_WaitTicks(uint16_t ticks) {
    if(ticks <= TMR1_POLL) {
        TMR1_WriteTimer((uint16_t)0);
        TMR1_StartTimer();
        while(TMR1_ReadTimer() < ticks);
        TMR1_StopTimer();
        return ticks;
    } else {
        uint16_t w = (ticks > TMR1_MAXWAIT) ? TMR1_MAXWAIT : ticks;
        w--; // Wait one tick less too correct waiting
        uint16_t period = (uint16_t)0xFFFF - w;
        // Fix in PIC-bug: SLEEP fails when transmitting USART data
        while(!TX1STAbits.TRMT);
        TMR1_WriteTimer(period);
        TMR1_StartTimer();
        SLEEP();
        NOP();
        TMR1_StopTimer();
        return TMR1_ReadTimer() - period;
    }
}