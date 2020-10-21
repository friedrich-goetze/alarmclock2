#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "alarm.h"
#include "simpletime.h"
#include "rtc.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/pwm3.h"
#include "mcc_generated_files/tmr0.h"



#define ALARM_REPETITIONS 10
#define DUTY_START 0x2FF
#define DUTY_END 0x400
#define DUTY_INC 0x1
#define HALF_BEEP_DURATION_MILLIS ((uint16_t)300)

#define SWITCH_OFF_DELAY_MILLIS ((uint16_t)8000)

uint16_t duty = 0x0; // PWM Max 1024 / 0x400
bool isBeepOn = false;
uint8_t repetitionsLeft = 0;
uint16_t beepToggleStartMillis = 0;

bool isOffSwitchActive = 0;
uint16_t offSwitchStart = 0;

SimpleTime almtime;

struct tm rtcc;

bool isEnabled = false;
bool isActive = false;

void ALARM_StartBeeping(void);

void ALARM_Init() {
    isEnabled = false;
    isActive = false;
    almtime.hours = 10;
    almtime.minutes = 0;
}

uint16_t ALARM_Update(uint16_t ticksSinceLastCall) {

    if (isActive) {
        // Important to not run again.
        // Must be enabled before each night.
        isEnabled = false;

        // Needed by a lot of code.
        uint16_t nowMillis = TMR0_ReadTimer();

        // Off switch is active.
        if (isOffSwitchActive) {
            uint16_t offTimeMillis = nowMillis - offSwitchStart;
            // Debounce check
            if (offTimeMillis > SWITCH_OFF_DELAY_MILLIS) {
                // Alarm is deactivated
                isActive = false;
            } else if (offTimeMillis > 1000) {
                // Check if is still active
                isOffSwitchActive = ALM_IN_PORT;
                if (!isOffSwitchActive) {
                    ALARM_StartBeeping();
                }
            }
        } else if (ALM_IN_PORT) {
            isOffSwitchActive = true;
            offSwitchStart = TMR0_ReadTimer();
        }

        if (isOffSwitchActive || !isActive) {
            PWM3_LoadDutyValue(0);
        } else {
            // Manage beeping
            uint16_t sinceStartMillis = nowMillis - beepToggleStartMillis;
            if (sinceStartMillis >= HALF_BEEP_DURATION_MILLIS) {
                isBeepOn = !isBeepOn;

                if (isBeepOn) {
                    duty += DUTY_INC;
                    if (duty >= DUTY_END) {
                        // Reached loudest point.
                        // Restart Repetition.
                        duty = DUTY_START;
                        repetitionsLeft--;
                        if (repetitionsLeft == 0) {
                            // Nobody disabled it... force of
                            isActive = false;
                        }
                    }
                }

                PWM3_LoadDutyValue((isActive && isBeepOn) ? duty : 0);

                beepToggleStartMillis += HALF_BEEP_DURATION_MILLIS;
            }
        }
    } else if (isEnabled) {
        SimpleTime daytime;
        RTC_GetTime(&daytime);

        printf("day: %u:%u alm: %u:%u\n", daytime.hours, daytime.minutes, almtime.hours, almtime.minutes);

        if (memcmp(&daytime, &almtime, sizeof (SimpleTime)) == 0) {
            // Alarm triggers.
            // Init all Fields
            isActive = true;
            ALARM_StartBeeping();
        }
    }

    return (isActive) ? 0x2 : 0xFFFF;
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
    *pTime = almtime;
}

void ALARM_SetTime(const SimpleTime* pTime) {
    almtime = *pTime;
}

void ALARM_StartBeeping() {
    duty = DUTY_START;
    repetitionsLeft = ALARM_REPETITIONS;
    beepToggleStartMillis = TMR0_ReadTimer();
    isBeepOn = true;
    isOffSwitchActive = false;
    PWM3_LoadDutyValue(duty);
}