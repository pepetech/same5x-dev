#include "rtsc.h"

void rstc_init()
{
    MCLK->APBAMASK.bit.RSTC_ = 1;
}

uint8_t rstc_get_reset_reason()
{
    return RSTC->RCAUSE.reg;
}