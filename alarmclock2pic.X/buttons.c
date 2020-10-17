#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "buttons.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr0.h"

#include "lcd_driver.h"

bool isDebounce;
uint16_t debounceStartMillis;
uint16_t debounceLeftMillis;

uint8_t curButton;
bool curButtonJustPressed;

uint8_t BTN_CreateBits();
void BTN_InterruptHandler(void);
void BTN_StartDebounce(uint16_t millis);
void BTN_EndDebounce(void);

void BTN_Init() {
    curButton = BTN_NONE;
    curButton = false;
    debounceStartMillis = 0;
    debounceLeftMillis = 0;
    isDebounce = false;
}

uint16_t BTN_Update(uint16_t ticksSinceLastCall) {
    if (isDebounce) {
        uint16_t t = TMR0_ReadTimer();
        uint16_t d = t - debounceStartMillis;
        if (d >= debounceLeftMillis) {
            // Debounce period is over
            BTN_EndDebounce();
        } else {
            debounceStartMillis = t;
            debounceLeftMillis -= d;
        }
        // Do not let scheduler wait until debounce period is over
        return 0;
    }

    uint8_t bits = BTN_CreateBits();

    uint8_t action = 0;

    if (curButton) {
        // Pressed button
        // BTN_Update called second time. This button is down but no longer pressed.
        curButtonJustPressed = false;

        if (!(bits & curButton)) {
            // Button is up, release it
            curButton = BTN_NONE;
            BTN_StartDebounce(50);
            action = 1;
        }
    } else if (bits) {
        // A button is down, find out which one.
        // Note, that multiple buttons could be pressed, but we need only one.
        if (bits & BTN_MODE) {
            curButton = BTN_MODE;
        } else if (bits & BTN_SET) {
            curButton = BTN_SET;
        } else if (bits & BTN_INC) {
            curButton = BTN_INC;
        } else if (bits & BTN_DEC) {
            curButton = BTN_DEC;
        }

        curButtonJustPressed = true;
        BTN_StartDebounce(50);
        action = 1;
    }

    if (action) {
        char* lcd = LCD_TakeBuffer();
        uint8_t ch = '0';
        switch (curButton) {
            case BTN_MODE: ch = 'm';
                break;
            case BTN_SET: ch = 's';
                break;
            case BTN_INC: ch = 'i';
                break;
            case BTN_DEC: ch = 'd';
                break;
        }
        lcd[LCD_TOTAL_CHARS - 1] = ch;
        LCD_PushBuffer();
    }

    // Can wait forever, since interrupt will wake up scheduler anyway
    return (isDebounce) ? 0 : 0xFFFF;
}

bool BTN_IsDown(uint8_t id);
bool BTN_IsPressed(uint8_t id);

void BTN_StartDebounce(uint16_t millis) {
    isDebounce = true;
    debounceStartMillis = TMR0_ReadTimer();
    debounceLeftMillis = millis;
    PIE0bits.IOCIE = 0; // Disable Button interrupts while debounce
}

void BTN_EndDebounce() {
    isDebounce = false;
    PIE0bits.IOCIE = 1; // Enable Button interrupts after debounce
}

uint8_t BTN_CreateBits() {
    uint8_t r = 0x00;
    if (BTN_MODE_PORT) {
        r |= BTN_MODE;
    }
    if (BTN_SET_PORT) {
        r |= BTN_SET;
    }
    if (BTN_INC_PORT) {
        r |= BTN_INC;
    }
    if (BTN_DEC_PORT) {
        r |= BTN_DEC;
    }
    return r;
}