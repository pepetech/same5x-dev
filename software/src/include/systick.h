#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include <sam.h>
#include "atomic.h"
#include "mclk.h"

extern volatile uint64_t g_ullSystemTick;

void systick_init();
void delay_ms(uint32_t ullTicks);
void delay_us(uint32_t ullTicks);

#endif