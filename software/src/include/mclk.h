#ifndef __MCLK_H__
#define __MCLK_H__

#include <sam.h>
#include "gclk.h"

extern uint32_t APB_HS_CLOCK_FREQ;
extern uint32_t APB_CPU_CLOCK_FREQ;
extern uint32_t AHB_CPU_CLOCK_FREQ;
extern uint32_t CPU_CLOCK_FREQ;

void mclk_init();
void mclk_update_clocks();

#endif // __MCLK_H__