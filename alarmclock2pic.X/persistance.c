#include <string.h>

#include "persistance.h"
#include "alarm.h"
#include "simpletime.h"
#include "rtc.h"
#include "mcc_generated_files/memory.h"

#define EE_ADDR (0xF000)

SimpleTime lastUpdate;

PERSISTANCE_Init() {
    PERSISTANCE_LoadState();
    RTC_GetTime(&lastUpdate);
}

uint16_t PERSISTANCE_Update(uint16_t ticksSinceLast) {
    SimpleTime now;
    RTC_GetTime(&now);

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
    RTC_GetTime(&daytime);
    ALARM_GetTime(&almtime);

    DATAEE_WriteByte(EE_ADDR + 0, daytime.hours);
    DATAEE_WriteByte(EE_ADDR + 1, daytime.minutes);
    DATAEE_WriteByte(EE_ADDR + 2, almtime.hours);
    DATAEE_WriteByte(EE_ADDR + 3, almtime.minutes);
}

PERSISTANCE_LoadState() {
    SimpleTime daytime;
    SimpleTime almtime;

    daytime.hours = DATAEE_ReadByte(EE_ADDR + 0) % 24;
    daytime.minutes = DATAEE_ReadByte(EE_ADDR + 1) % 60;
    almtime.hours = DATAEE_ReadByte(EE_ADDR + 2) % 24;
    almtime.minutes = DATAEE_ReadByte(EE_ADDR + 3) % 60;

    RTC_SetTime(&daytime);
    ALARM_SetTime(&almtime);
}