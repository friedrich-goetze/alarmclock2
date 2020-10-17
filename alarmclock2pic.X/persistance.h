#ifndef PERSISTANCE_H
#define	PERSISTANCE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

PERSISTANCE_Init(void);
uint16_t PERSISTANCE_Update(uint16_t ticksSinceLast);

PERSISTANCE_WriteState(void);
PERSISTANCE_LoadState(void);

#endif	/* XC_HEADER_TEMPLATE_H */

