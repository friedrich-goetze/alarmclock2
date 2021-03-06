#ifndef BUTTONS_H
#define	BUTTONS_H

#include <xc.h> // include processor files - each processor file is guarded.

#define BTN_NONE (0x0)
#define BTN_MODE (0x1)
#define BTN_SET (0x1 << 1)
#define BTN_INC (0x1 << 2)
#define BTN_DEC (0x1 << 3)

void BTN_Init(void);
uint16_t BTN_Update(uint16_t ticksSinceLastCall);

uint8_t BTN_GetDownButton(void);
bool BTN_IsButtonPressed(void);

#endif	/* XC_HEADER_TEMPLATE_H */

