#ifndef SIMPLETIME_H
#define	SIMPLETIME_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <time.h>

typedef struct __SIMPLETIME {
    uint8_t hours;
    uint8_t minutes;
} SimpleTime;

void SIMPLETIME_FromTime(const struct tm *pTM, SimpleTime* pDest);
void SIMPLETIME_ToTime(const SimpleTime* pST, struct tm *pDest);
/** Doesn't write null terminator. */
void SIMPLETIME_WriteStr(const SimpleTime* pST, char* pStr);

#endif	/* XC_HEADER_TEMPLATE_H */

