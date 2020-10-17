#include <xc.h>
#include "scheduler.h"
#include "mcc_generated_files/eusart1.h"
#include "mcc_generated_files/tmr1.h"

#define TMR1_POLL ((uint16_t)4)
#define TMR1_MAXWAIT ((uint16_t)0xFFFF - TMR1_POLL)

volatile bool interrupted;

void TMR_Interrupt() {
}

void SCHEDULE_API_InitWaitTicks() {
    TMR1_SetInterruptHandler(TMR_Interrupt);
    TMR1_StopTimer();
    interrupted = false;
}

uint16_t SCHEDULE_API_WaitTicks(uint16_t ticks) {
    if(ticks <= TMR1_POLL || true) {
        TMR1_WriteTimer((uint16_t)0);
        TMR1_StartTimer();
        while(TMR1_ReadTimer() < ticks && !interrupted);
        TMR1_StopTimer();
        
        interrupted = false;
        
        return TMR1_ReadTimer();
    } else {
        uint16_t w = (ticks > TMR1_MAXWAIT) ? TMR1_MAXWAIT : ticks;
        w--; // Wait one tick less too correct waiting
        uint16_t period = (uint16_t)0xFFFF - w;
        // Fix in PIC-bug: SLEEP fails when transmitting USART data
        TMR1_WriteTimer(period);
        TMR1_StartTimer();
        while(!EUSART1_is_tx_ready() || !EUSART1_is_tx_done());
        SLEEP();
        NOP();
        TMR1_StopTimer();
        
        interrupted = false;
        
        return TMR1_ReadTimer() - period;
    }
}

void SCHEDULE_API_OnInterrupt(void) {
    interrupted = true;
}