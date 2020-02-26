
#ifndef __PORT_H__
#define __PORT_H__

#include <sam.h>
#include "utils.h"

void port_init();

// LED MACROS
#define LED_HIGH()          PORT->Group[0].OUTSET.reg = BIT(26)
#define LED_LOW()           PORT->Group[0].OUTCLR.reg = BIT(26)
#define LED_TOGGLE()        PORT->Group[0].OUTTGL.reg = BIT(26)

#endif  // __PORT_H__