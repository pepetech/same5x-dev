#ifndef __GCLK_H__
#define __GCLK_H__

#include <sam.h>
#include "mclk.h"

extern uint32_t GCLK_CLOCK_FREQ[12];

void gclk_init();
void gclk_update_clocks();

#endif // __GCLK_H__