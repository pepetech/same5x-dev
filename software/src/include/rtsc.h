#ifndef __RSTC_H__
#define __RSTC_H__

#include <sam.h>

void rstc_init();
uint8_t rstc_get_reset_reason();

#endif // __RSTC_H__