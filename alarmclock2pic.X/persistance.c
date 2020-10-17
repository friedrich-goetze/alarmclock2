#include <string.h>

#include "persistance.h"
#include "alarm.h"
#include "simpletime.h"
#include "mcc_generated_files/rtcc.h"
#include "mcc_generated_files/memory.h"

#define EE_ADDR (0xF000)

struct tm rtcc;
SimpleTime lastUpdate;

PERSISTANCE_Init() {
    PERSISTANCE_LoadState();
    RTCC_TimeGet(&rtcc);
    SIMPLETIME_FromTime(&rtcc, &lastUpdate);
}

uint16_t PERSISTANCE_Update(uint16_t ticksSinceLast) {
    SimpleTime now;
    RTCC_TimeGet(&rtcc);
    SIMPLETIME_FromTime(&rtcc, &now);

    if (memcmp(&now, &lastUpdate, sizeof (SimpleTime)) && now.minutes % 5 == 0) {
        lastUpdate = now;
        PERSISTANCE_WriteState();
    }

    return 0xFFFF;
}

PERSISTANCE_WriteState() {
    // Get data we want to write
    SimpleTime daytime;
    SimpleTime almtime;

    RTCC_TimeGet(&rtcc);
    SIMPLETIME_FromTime(&rtcc, &daytime);
    ALARM_GetTime(&almtime);

    DATAEE_WriteByte(EE_ADDR + 0, daytime.hours);
    DATAEE_WriteByte(EE_ADDR + 1, daytime.minutes);
    DATAEE_WriteByte(EE_ADDR + 2, almtime.hours);
    DATAEE_WriteByte(EE_ADDR + 3, almtime.minutes);

    printf("W\n");
}

PERSISTANCE_LoadState() {
    SimpleTime daytime;
    SimpleTime almtime;

    // For initialization
    RTCC_TimeGet(&rtcc);

    daytime.hours = DATAEE_ReadByte(EE_ADDR + 0) % 24;
    daytime.minutes = DATAEE_ReadByte(EE_ADDR + 1) % 60;
    almtime.hours = DATAEE_ReadByte(EE_ADDR + 2) % 24;
    almtime.minutes = DATAEE_ReadByte(EE_ADDR + 3) % 60;

    SIMPLETIME_ToTime(&daytime, &rtcc);
    RTCC_TimeSet(&rtcc);

    ALARM_SetTime(&almtime);
}