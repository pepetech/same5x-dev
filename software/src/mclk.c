#include "mclk.h"

uint32_t APB_HS_CLOCK_FREQ;
uint32_t APB_CPU_CLOCK_FREQ;
uint32_t AHB_CPU_CLOCK_FREQ;
uint32_t CPU_CLOCK_FREQ;

void mclk_init()
{
    MCLK->CPUDIV.reg = 0x01; // cpu clk divider
    while(!(MCLK->INTFLAG.bit.CKRDY));
}

void mclk_update_clocks()
{
    uint32_t div = MCLK->CPUDIV.reg;
    APB_CPU_CLOCK_FREQ = AHB_CPU_CLOCK_FREQ = CPU_CLOCK_FREQ = (GCLK_CLOCK_FREQ[0] / div);

    div = MCLK->HSDIV.reg;
    APB_HS_CLOCK_FREQ = (GCLK_CLOCK_FREQ[0] / div);
}