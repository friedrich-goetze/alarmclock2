#include "rtc.h"
#include "mcc_generated_files/rtcc.h"

void RTC_Init() {
    RTC_Update(0);
}

struct tm rtccTm;
SimpleTime daytime;

uint16_t RTC_Update(uint16_t ticksSinceLast) {
    RTCC_TimeGet(&rtccTm);
    SIMPLETIME_FromTime(&rtccTm, &daytime);
    return 0xFFFF;
}

void RTC_GetTime(SimpleTime* pST) {
    *pST = daytime;
}

void RTC_SetTime(const SimpleTime* pST) {
    daytime = *pST;
    SIMPLETIME_ToTime(&daytime, &rtccTm);
    RTCC_TimeSet(&rtccTm);
}