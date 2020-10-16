#ifndef BUTTONS_H
#define	BUTTONS_H

#include <xc.h> // include processor files - each processor file is guarded.

typedef struct __BTN_Status {
    uint16_t _millis;
    uint8_t _lifecycle : 4;
    bool isDown : 1;
    bool hasJustChanged : 1;
} BTN_Status;

typedef struct __BTN_AllStatus {
    BTN_Status mode;
    BTN_Status set;
    BTN_Status inc;
    BTN_Status dec;
} BTN_AllStatus;

void BTN_Init(void);
uint16_t BTN_Update(uint16_t ticksSinceLastCall);
BTN_AllStatus* BTN_GetStatus(void);

#endif	/* XC_HEADER_TEMPLATE_H */

