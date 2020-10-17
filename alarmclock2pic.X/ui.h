#ifndef XC_UI_H
#define	XC_UI_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>
#include <stdbool.h>

void UI_Init(void);
uint16_t UI_Update(uint16_t ticksSinceLastCall);

#endif	/* XC_HEADER_TEMPLATE_H */

