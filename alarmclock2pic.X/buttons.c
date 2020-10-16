#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "buttons.h"

BTN_AllStatus bas;

void BTN_Init() {
    memset(&bas, 0, sizeof (bas));
}

uint16_t BTN_Update(uint16_t ticksSinceLastCall) {
    return 0xFFFF;
}

BTN_AllStatus* BTN_GetStatus() {
    return &bas;
}