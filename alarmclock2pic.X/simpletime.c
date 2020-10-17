#include "simpletime.h"
#include <string.h>
#include <stdio.h>

char stChBuf[] = "00:00";

void SIMPLETIME_FromTime(const struct tm *pTM, SimpleTime* pDest) {
    pDest->hours = (uint8_t) pTM->tm_hour;
    pDest->minutes = (uint8_t) pTM->tm_min;
}

void SIMPLETIME_ToTime(const SimpleTime* pST, struct tm *pDest) {
    pDest->tm_hour = pST->hours;
    pDest->tm_min = pST->minutes;
}

void SIMPLETIME_WriteStr(const SimpleTime* pST, char* pStr) {
    snprintf(stChBuf, 6, "%02d:%02d", pST->hours, pST->minutes);
    memcpy(pStr, stChBuf, 5);
}