#include "port.h"

#define PORT_PIN_MUX_SEL_(group, pin, val) if(pin & 0x01){PORT->Group[group].PMUX[pin >> 1].bit.PMUXO = val;}else{PORT->Group[group].PMUX[pin >> 1].bit.PMUXE = val;}
#define PORT_PIN_PULL_SET_(group, pin, val) PORT->Group[group].PINCFG[pin].bit.PULLEN = val
#define PORT_PIN_DRVSTR_SET_(group, pin, val) PORT->Group[group].PINCFG[pin].bit.DRVSTR = val
#define PORT_PIN_INEN_SET_(group, pin, val) PORT->Group[group].PINCFG[pin].bit.INEN = val
#define PORT_PIN_PMUXEN_SET_(group, pin, val) PORT->Group[group].PINCFG[pin].bit.PMUXEN = val

void port_init()
{
    MCLK->APBBMASK.bit.PORT_ = 1;

    /* PORT A */
    // direction
    PORT->Group[0].DIRCLR.reg = 0xFFFFFFFF;  // inputs
    PORT->Group[0].DIRSET.reg = BIT(26);  // outputs
    // output / pull select
    PORT->Group[0].OUTCLR.reg = 0xFFFFFFFF;  // output low / pull down
    PORT->Group[0].OUTSET.reg = BIT(26);  // output high / pull up

    /* PORT B */
    // direction
    PORT->Group[1].DIRCLR.reg = 0xFFFFFFFF;  // inputs
    PORT->Group[1].DIRSET.reg = BIT(30);  // outputs
    // output / pull select
    PORT->Group[1].OUTCLR.reg = 0xFFFFFFFF;  // output low / pull down
    PORT->Group[1].OUTSET.reg = 0;  // output high / pull up

    PORT_PIN_MUX_SEL_(1, 30, 0x7); // PB30 mux H (swo trace)
    PORT_PIN_DRVSTR_SET_(1, 30, 1); // high drive strength
    PORT_PIN_PMUXEN_SET_(1, 30, 1); // enable peripheral mux
}