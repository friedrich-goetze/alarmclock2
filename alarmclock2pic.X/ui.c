#include <string.h>

#include "ui.h"
#include "alarm.h"
#include "buttons.h"
#include "mcc_generated_files/rtcc.h"
#include "simpletime.h"
#include "lcd_driver.h"
#include "mcc_generated_files/tmr0.h"
#include "persistance.h"

#define UI_HOME 0
#define UI_SET_BIT (0b1)
#define UI_SET_TIME (0b10 | UI_SET_BIT)
#define UI_SET_ALM (0b100 | UI_SET_BIT)
#define UI_ENABLE_ALM (0b1000 | UI_SET_BIT)
#define UI_ALARM_ACTIVE (0b10000)

#define UI_SETSTEP_SELECT 0
#define UI_SETSTEP_HOURS 1
#define UI_SETSTEP_TEN_MINUTES 2
#define UI_SETSTEP_MINUTES 3
#define UI_SETSTEP_LASTSTEP 3

typedef struct __UI_Data {
    uint8_t mode;
    uint8_t setStep;
    SimpleTime dayTime;
    SimpleTime almTime;

} UI_Data;

#define TIMEOUT ((uint16_t)0x7500)
uint16_t lastPressMillis = 0;

UI_Data ui;
struct tm rtcc;

// Used for times which aren't shown anyway.
const SimpleTime dummyTime = {.hours = 0, .minutes = 0};

void UI_Init() {
    ui.mode = UI_HOME;
    ui.setStep = UI_SETSTEP_SELECT;
}

uint8_t UI_IncDecRanged(bool inc, uint8_t value, uint8_t amount, uint8_t max);

uint16_t UI_Update(uint16_t ticksSinceLastCall) {
    // Gather data from environment.
    bool isAlarmActive = ALARM_IsActive();
    bool isAlarmEnabled = ALARM_IsEnabled();
    uint8_t btn = BTN_GetDownButton();
    uint16_t curMillis = TMR0_ReadTimer();
    RTCC_TimeGet(&rtcc);

    // Create a copy to check, if anything has changed that requires a redraw.
    UI_Data newUI = ui;

    // Active alarm can disable interactive ui.
    // After disableing alarm, go back to home.
    if (isAlarmActive) {
        newUI.mode = UI_ALARM_ACTIVE;
    } else if (newUI.mode == UI_ALARM_ACTIVE) {
        newUI.mode = UI_HOME;
    }

    // Buttons are ignored, if alarm is active.
    // Process pressed buttons.
    // That are buttons, which are seen down the first time.
    if (!isAlarmActive && btn && BTN_IsButtonPressed()) {

        switch (btn) {

            case BTN_MODE:
                if (newUI.mode == UI_HOME || newUI.setStep == UI_SETSTEP_SELECT) {
                    // Toggle through modes
                    switch (newUI.mode) {
                        case UI_HOME:
                            newUI.mode = UI_ENABLE_ALM;
                            break;
                        case UI_ENABLE_ALM:
                            newUI.mode = UI_SET_ALM;
                            break;
                        case UI_SET_ALM:
                            newUI.mode = UI_SET_TIME;
                            break;
                        default:
                            newUI.mode = UI_HOME;
                            break;
                    }

                    // Init freshly entered mode
                    newUI.setStep = UI_SETSTEP_SELECT;
                }
                break;

            case BTN_SET:
                // Set does only sth in set mode
                if (!(newUI.mode & UI_SET_BIT)) break;

                if (newUI.mode == UI_ENABLE_ALM) {
                    // Toggle enable flag and go back to home
                    isAlarmEnabled = !isAlarmEnabled;
                    ALARM_SetEnabled(isAlarmEnabled);
                    newUI.mode = UI_HOME;
                } else if (newUI.setStep < UI_SETSTEP_LASTSTEP) {
                    // Just go to next
                    newUI.setStep++;
                    break;
                } else {
                    // Last Step finished, apply changes
                    switch (newUI.mode) {
                        case UI_SET_TIME:
                            SIMPLETIME_ToTime(&newUI.dayTime, &rtcc);
                            RTCC_TimeSet(&rtcc);
                            break;
                        case UI_SET_ALM:
                            ALARM_SetTime(&newUI.almTime);
                            break;
                    }

                    PERSISTANCE_WriteState();

                    newUI.mode = UI_HOME;
                }

                break;

            case BTN_INC:
            case BTN_DEC:
                if (newUI.mode != UI_SET_TIME && newUI.mode != UI_SET_ALM) break;

                SimpleTime* pEdit = (newUI.mode == UI_SET_TIME)
                        ? &newUI.dayTime
                        : &newUI.almTime;

                bool inc = (btn == BTN_INC);
                uint8_t maxDigit;
                uint8_t minDigit;

                switch (newUI.setStep) {
                    case UI_SETSTEP_HOURS:
                        pEdit->hours = UI_IncDecRanged(inc, pEdit->hours, 1, 24);
                        break;
                    case UI_SETSTEP_TEN_MINUTES:
                    case UI_SETSTEP_MINUTES:
                        maxDigit = pEdit->minutes / 10;
                        minDigit = pEdit->minutes % 10;

                        if (newUI.setStep == UI_SETSTEP_TEN_MINUTES) {
                            maxDigit = UI_IncDecRanged(inc, maxDigit, 1, 6);
                        } else {
                            minDigit = UI_IncDecRanged(inc, minDigit, 1, 10);
                        }

                        pEdit->minutes = maxDigit * 10 + minDigit;
                        break;
                }

                break;
        }
    }

    // Not in set-mode, update daytime and alarm-time
    if (newUI.mode == UI_HOME) {
        SIMPLETIME_FromTime(&rtcc, &newUI.dayTime);
        ALARM_GetTime(&newUI.almTime);

    } else if (BTN_IsButtonPressed()) {
        // Reset Timeout
        lastPressMillis = curMillis;
    } else if (curMillis - lastPressMillis > TIMEOUT) {
        // Timeout
        newUI.mode = UI_HOME;
    }
    // Fix any severe errors which shouldn't exist
    newUI.dayTime.hours %= 24;
    newUI.dayTime.minutes %= 60;
    newUI.almTime.hours %= 24;
    newUI.almTime.minutes %= 60;

    // Update screen, if anything has changed
    if (memcmp(&ui, &newUI, sizeof (UI_Data))) {
        ui = newUI;

        char* lcd = LCD_TakeBuffer();

        memset(lcd, ' ', LCD_TOTAL_CHARS);

        // Layout
        //     0123456789ABCDEF
        // 0       hh:mm    SET
        // 1   ALM hh:mm    SET

        // Daytime
        SIMPLETIME_WriteStr(&newUI.dayTime, lcd + 0x04);

        // Time Set Text
        if (newUI.mode == UI_SET_TIME) {
            memcpy(lcd + 0x0D, "SET", 3);
        }

        // Alm Text
        memcpy(lcd + 0x10, "ALM", 3);

        // Show alarm time if in set mode or alarm is enabled
        if (newUI.mode == UI_ENABLE_ALM) {
            if (isAlarmEnabled) {
                memcpy(lcd + 0x14, "Disable", 7);
            } else {
                memcpy(lcd + 0x14, "Enable", 6);
            }
        } else if (isAlarmEnabled || (newUI.mode & UI_SET_BIT)) {
            SIMPLETIME_WriteStr(&newUI.almTime, lcd + 0x14);
        } else {
            memcpy(lcd + 0x14, "Off", 3);
        }

        // Alarm Set Text
        if (newUI.mode == UI_SET_ALM) {
            memcpy(lcd + 0x1D, "SET", 3);
        }

        // Write Text
        LCD_PushBuffer();

        // Set cursor
        // Important to do after LCD_PushBuffer
        if ((newUI.mode == UI_SET_TIME || newUI.mode == UI_SET_ALM) && newUI.setStep > UI_SETSTEP_SELECT) {
            uint8_t pos = 0; // 0 also means no cursor
            switch (newUI.setStep) {
                case UI_SETSTEP_HOURS:
                    pos = 5;
                    break;
                case UI_SETSTEP_TEN_MINUTES:
                    pos = 7;
                    break;
                case UI_SETSTEP_MINUTES:
                    pos = 8;
                    break;
            }

            if (pos) {
                LCD_ShowCursor(
                        (newUI.mode == UI_SET_ALM) ? 1 : 0,
                        pos,
                        LCD_CURSOR_SOLID
                        );
            } else {
                LCD_ShowCursor(0, 0, LCD_CURSOR_OFF);
            }
        } else if (newUI.mode == UI_ENABLE_ALM) {
            LCD_ShowCursor(
                    1,
                    0x4,
                    LCD_CURSOR_SOLID
                    );
        } else {
            LCD_ShowCursor(0, 0, LCD_CURSOR_OFF);
        }
    }

    // Wait forever if is in home, otherwise wait a second to re-check timeout.
    return (newUI.mode == UI_HOME) ? 0xFFFF : 0x7FFF;
}

uint8_t UI_IncDecRanged(bool inc, uint8_t value, uint8_t amount, uint8_t max) {
    if (inc) {
        uint8_t r = value + amount;
        return (r < max) ? r : r % max;
    } else {
        return (value >= amount) ? value - amount : max - (amount - value);
    }
}