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
    curButtonJustPressed = false; // This is enabled only for one tick
    
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

    if (curButton) {
        if (!(bits & curButton)) {
            // Button is up, release it
            curButton = BTN_NONE;
            BTN_StartDebounce(50);
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
    }

    // Can wait forever, since interrupt will wake up scheduler anyway
    return (isDebounce) ? 0 : 0xFFFF;
}

uint8_t BTN_GetDownButton() {
    return curButton;
}

bool BTN_IsButtonPressed(void) {
    return curButtonJustPressed;
}

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