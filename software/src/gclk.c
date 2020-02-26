#include "gclk.h"

// TODO: OSCCTRL
uint32_t XOSC0_CLOCK_FREQ = 0;
uint32_t XOSC1_CLOCK_FREQ = 0;
uint32_t DFLL48M_CLOCK_FREQ = 48000000UL;
uint32_t DPLL0_CLOCK_FREQ = 0;
uint32_t DPLL1_CLOCK_FREQ = 0;

// TODO: OSC32KCTRL
uint32_t XOSC32K_CLOCK_FREQ = 0;
uint32_t OSCULP32K_CLOCK_FREQ = 0;

uint32_t GCLK_CLOCK_FREQ[12];


void gclk_init()
{
    MCLK->APBAMASK.bit.GCLK_ = 1; // enable APB bus clock mask
    GCLK->CTRLA.bit.SWRST = 1;  // reset gclk
    while(GCLK->CTRLA.bit.SWRST); // wait for reset

    /* GCLK0 config (used for MCLK) */
    GCLK->GENCTRL[0].bit.SRC = GCLK_GENCTRL_SRC_DFLL_Val; // select dfll (48MHz)
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[0].bit.DIV = 1; // no divide
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[0].bit.DIVSEL = 0; // divide mode
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[0].bit.GENEN = 1;
    while(GCLK->SYNCBUSY.vec.GENCTRL);

    volatile uint8_t test = 0;

    /* GCLK1 config */
    GCLK->GENCTRL[1].bit.SRC = GCLK_GENCTRL_SRC_DFLL_Val; // select dfll (48MHz)
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[1].bit.DIV = 1; // no divide
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[1].bit.DIVSEL = 0; // divide mode
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[1].bit.GENEN = 1;
    while(GCLK->SYNCBUSY.vec.GENCTRL);

    /* GCLK2 config */
    GCLK->GENCTRL[2].bit.SRC = GCLK_GENCTRL_SRC_DFLL_Val; // select dfll (48MHz)
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[2].bit.DIV = 2; // no divide
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[2].bit.DIVSEL = 0; // divide mode
    while(GCLK->SYNCBUSY.vec.GENCTRL);
    GCLK->GENCTRL[2].bit.GENEN = 1;
    while(GCLK->SYNCBUSY.vec.GENCTRL);

    /* GCLK3 config */
    /* GCLK4 config */
    /* GCLK5 config */
    /* GCLK6 config */
    /* GCLK7 config */
    /* GCLK8 config */
    /* GCLK9 config */
    /* GCLK10 config */
    /* GCLK11 config */

    while(GCLK->SYNCBUSY.vec.GENCTRL); // wait for clock syncronization
}

void gclk_update_clocks()
{
    uint8_t i = 1;
    do
    {
        if(i == 12) i = 0;

        if(GCLK->GENCTRL[i].bit.GENEN)
        {
            switch(GCLK->GENCTRL[i].bit.SRC)
            {
            case 0x0: // XOSC 0 oscillator output
                GCLK_CLOCK_FREQ[i] = XOSC0_CLOCK_FREQ;
                break;
            case 0x1: // XOSC 1 oscillator output
                GCLK_CLOCK_FREQ[i] = XOSC1_CLOCK_FREQ;
                break;
            case 0x2: // Generator input pad (GCLK_IO)
                GCLK_CLOCK_FREQ[i] = 0;
                break;
            case 0x3: // Generic clock generator 1 output
                GCLK_CLOCK_FREQ[i] = GCLK_CLOCK_FREQ[1];
                break;
            case 0x4: // OSCULP32K oscillator output
                GCLK_CLOCK_FREQ[i] = OSCULP32K_CLOCK_FREQ;
                break;
            case 0x5: // XOSC32K oscillator output
                GCLK_CLOCK_FREQ[i] = XOSC32K_CLOCK_FREQ;
                break;
            case 0x6: // DFLL oscillator output
                GCLK_CLOCK_FREQ[i] = DFLL48M_CLOCK_FREQ;
                break;
            case 0x7: // DPLL0 output
                GCLK_CLOCK_FREQ[i] = DPLL0_CLOCK_FREQ;
                break;
            case 0x8: // DPLL1 output
                GCLK_CLOCK_FREQ[i] = DPLL1_CLOCK_FREQ;
                break;
            default: // XOSC 0 oscillator output
                GCLK_CLOCK_FREQ[i] = 0;
                break;
            }

            volatile uint32_t ulDivSel = GCLK->GENCTRL[i].bit.DIVSEL;
            volatile uint32_t ulDiv = GCLK->GENCTRL[i].bit.DIV;

            if(ulDiv)
            {
                if(ulDivSel == 0)
                {
                    GCLK_CLOCK_FREQ[i] /= ulDiv;
                }
                else
                {
                    GCLK_CLOCK_FREQ[i] /= (2^(ulDiv));
                }
            }
        }
        else
        {
            GCLK_CLOCK_FREQ[i] = 0;
        }

    }
    while((i++) != 0);
}