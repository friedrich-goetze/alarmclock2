#ifndef ALARM_H
#define	ALARM_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>
#include "simpletime.h"

void ALARM_Init();
uint16_t ALARM_Update(uint16_t ticksSinceLastCall);
bool ALARM_IsEnabled(void);
bool ALARM_IsActive(void);
void ALARM_SetEnabled(bool enabled);
void ALARM_GetTime(SimpleTime* pTime);
void ALARM_SetTime(const SimpleTime* pTime);


#endif	/* XC_HEADER_TEMPLATE_H */

