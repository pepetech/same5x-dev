#include "rtsc.h"

uint8_t rstc_get_reset_reason()
{
    return RSTC->RCAUSE.reg;
}