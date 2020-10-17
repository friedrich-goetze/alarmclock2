#include "alarm.h"

bool isEnabled = false;
bool isActive = false;

void ALARM_Init() {
    isEnabled = false;
    isActive = false;
}

uint16_t ALARM_Update(uint16_t ticksSinceLastCall) {
    return 0xFFFF;
}

bool ALARM_IsEnabled(void) {
    return isEnabled;
}

bool ALARM_IsActive(void) {
    return isActive;
}

void ALARM_SetEnabled(bool enabled) {
    isEnabled = enabled;
}

void ALARM_GetTime(SimpleTime* pTime) {

}

void ALARM_SetTime(const SimpleTime* pTime) {

}