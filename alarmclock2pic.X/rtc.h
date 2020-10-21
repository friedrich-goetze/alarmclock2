
#ifndef RTC_H
#define	RTC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "simpletime.h"

void RTC_Init(void);
uint16_t RTC_Update(uint16_t);
void RTC_GetTime(SimpleTime* pST);
void RTC_SetTime(const SimpleTime* pST);

#endif	/* XC_HEADER_TEMPLATE_H */

