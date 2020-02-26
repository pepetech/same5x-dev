/**
 * startup file for SAME51
 *
 * Copyright (c) 2020 Rafael Silva
 *
 * SPDX-License-Identifier: MIT
 */

#include <sam.h>

extern void _estack(); // Not really a function, just to be compatible with array later

extern uint32_t _svect; // ISR Vectors
extern uint32_t _evect;

extern uint32_t _stext; // Main program
extern uint32_t _etext;

extern uint32_t _sidata; // Data source
extern uint32_t _sdata; // Data destination
extern uint32_t _edata;

extern uint32_t _sbss; // BSS destination
extern uint32_t _ebss;

extern uint32_t _end;


void _default_isr()
{
    while(1);
}

void __attribute__ ((weak)) __libc_init_array()
{

}

extern int init();
extern int main();

#define DEFAULT_ISR "_default_isr"

void _reset_isr()
{
    uint32_t *src, *dst;

    src = &_sidata;
    dst = &_sdata;

   while (dst < &_edata) // Copy data
        *(dst++) = *(src++);

    src = 0;
    dst = &_sbss;

    while (dst < &_ebss) // Zero BSS
        *(dst++) = 0;

    __libc_init_array();

    SCB->VTOR = (uint32_t)&_svect; // ISR Vectors offset
    SCB->AIRCR = 0x05FA0000 | (5 << 8); // Interrupt priority - 2 bits Group, 1 bit Sub-group
    SCB->SHCSR = SCB_SHCSR_USGFAULTENA_Msk | SCB_SHCSR_BUSFAULTENA_Msk | SCB_SHCSR_MEMFAULTENA_Msk; // Enable separate fault _isr()s
    SCB->SCR |= SCB_SCR_SEVONPEND_Msk; // Pending disabled interrupt generates event
    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk; // Enable division by zero faults
    SCB->CPACR |= 0xF << 20; // Enable CP10 & CP11 (FPU) in priv. and non priv. mode

    init();
    main();

    __disable_irq();
    while(1);
}

/* Cortex-M4 core ISR */
void _nmi_isr()                           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _hardfault_isr()                     __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _memmanage_isr()                     __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _busfault_isr()                      __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _usagefault_isr()                    __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _svc_isr()                           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _debugmon_isr()                      __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _pendsv_isr()                        __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _systick_isr()                       __attribute__ ((weak,  alias (DEFAULT_ISR)));

/* Peripherals ISR */
void _pm_isr()              __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _mclk_isr()            __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _oscctrl_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _oscctrl_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _oscctrl_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _oscctrl_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _oscctrl_4_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _osc32kctrl_isr()      __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _supc_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _supc_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _wdt_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _rtc_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_0_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_1_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_2_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_3_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_4_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_5_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_6_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_7_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_8_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_9_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_10_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_11_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_12_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_13_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_14_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _eic_15_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _freqm_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _nvmctrl_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _nvmctrl_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dmac_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dmac_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dmac_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dmac_3_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dmac_4_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _evsys_0_isr()         __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _evsys_1_isr()         __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _evsys_2_isr()         __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _evsys_3_isr()         __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _evsys_4_isr()         __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _pac_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _ramecc_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom0_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom0_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom0_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom0_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom1_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom1_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom1_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom1_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom2_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom2_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom2_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom2_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom3_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom3_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom3_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom3_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
#ifdef ID_SERCOM4
void _sercom4_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom4_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom4_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom4_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_SERCOM5
void _sercom5_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom5_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom5_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom5_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_SERCOM6
void _sercom6_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom6_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom6_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom6_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_SERCOM7
void _sercom7_0_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom7_1_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom7_2_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _sercom7_3_isr()       __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_CAN0
void _can0__isr()            __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_CAN1
void _can1__isr()            __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_USB
void _usb_0_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _usb_1_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _usb_2_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _usb_3_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_GMAC
void _gmac_isr()            __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
void _tcc0_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc0_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc0_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc0_3_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc0_4_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc0_5_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc0_6_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc1_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc1_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc1_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc1_3_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc1_4_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc2_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc2_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc2_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc2_3_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
#ifdef ID_TCC3
void _tcc3_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc3_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc3_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_TCC4
void _tcc4_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc4_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tcc4_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
void _tc0_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tc1_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tc2_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _tc3_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#ifdef ID_TC4
void _tc4_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_TC5
void _tc5_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_TC6
void _tc6_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_TC7
void _tc7_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
void _pdec_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _pdec_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _pdec_2_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _adc0_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _adc0_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _adc1_0_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _adc1_1_isr()          __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _ac_isr()              __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dac_0_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dac_1_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dac_2_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dac_3_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _dac_4_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
#ifdef ID_I2S
void _i2s_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
void _pcc_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _aes_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
void _trng_isr()            __attribute__ ((weak,  alias (DEFAULT_ISR)));
#ifdef ID_ICM
void _icm_isr()             __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_PUKCC
void _pukcc_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
void _qspi_isr()            __attribute__ ((weak,  alias (DEFAULT_ISR)));
#ifdef ID_SDHC0
void _sdhc0_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif
#ifdef ID_SDHC1
void _sdhc1_isr()           __attribute__ ((weak,  alias (DEFAULT_ISR)));
#endif


__attribute__ ((section(".isr_vector"))) void (* const g_pfnVectors[])() = {
    _estack,
    _reset_isr,
    _nmi_isr,
    _hardfault_isr,
    _memmanage_isr,
    _busfault_isr,
    _usagefault_isr,
    0,
    0,
    0,
    0,
    _svc_isr,
    _debugmon_isr,
    0,
    _pendsv_isr,
    _systick_isr,
    _pm_isr,
    _mclk_isr,
    _oscctrl_0_isr,
    _oscctrl_1_isr,
    _oscctrl_2_isr,
    _oscctrl_3_isr,
    _oscctrl_4_isr,
    _osc32kctrl_isr,
    _supc_0_isr,
    _supc_1_isr,
    _wdt_isr,
    _rtc_isr,
    _eic_0_isr,
    _eic_1_isr,
    _eic_2_isr,
    _eic_3_isr,
    _eic_4_isr,
    _eic_5_isr,
    _eic_6_isr,
    _eic_7_isr,
    _eic_8_isr,
    _eic_9_isr,
    _eic_10_isr,
    _eic_11_isr,
    _eic_12_isr,
    _eic_13_isr,
    _eic_14_isr,
    _eic_15_isr,
    _freqm_isr,
    _nvmctrl_0_isr,
    _nvmctrl_1_isr,
    _dmac_0_isr,
    _dmac_1_isr,
    _dmac_2_isr,
    _dmac_3_isr,
    _dmac_4_isr,
    _evsys_0_isr,
    _evsys_1_isr,
    _evsys_2_isr,
    _evsys_3_isr,
    _evsys_4_isr,
    _pac_isr,
    0,
    0,
    0,
    _ramecc_isr,
    _sercom0_0_isr,
    _sercom0_1_isr,
    _sercom0_2_isr,
    _sercom0_3_isr,
    _sercom1_0_isr,
    _sercom1_1_isr,
    _sercom1_2_isr,
    _sercom1_3_isr,
    _sercom2_0_isr,
    _sercom2_1_isr,
    _sercom2_2_isr,
    _sercom2_3_isr,
    _sercom3_0_isr,
    _sercom3_1_isr,
    _sercom3_2_isr,
    _sercom3_3_isr,
#ifdef ID_SERCOM4
    _sercom4_0_isr,
    _sercom4_1_isr,
    _sercom4_2_isr,
    _sercom4_3_isr,
#else
    0,
    0,
    0,
    0,
#endif
#ifdef ID_SERCOM5
    _sercom5_0_isr,
    _sercom5_1_isr,
    _sercom5_2_isr,
    _sercom5_3_isr,
#else
    0,
    0,
    0,
    0,
#endif
#ifdef ID_SERCOM6
    _sercom6_0_isr,
    _sercom6_1_isr,
    _sercom6_2_isr,
    _sercom6_3_isr,
#else
    0,
    0,
    0,
    0,
#endif
#ifdef ID_SERCOM7
    _sercom7_0_isr,
    _sercom7_1_isr,
    _sercom7_2_isr,
    _sercom7_3_isr,
#else
    0,
    0,
    0,
    0,
#endif
#ifdef ID_CAN0
    _can0__isr,
#else
    0,
#endif
#ifdef ID_CAN1
    _can1__isr,
#else
    0,
#endif
#ifdef ID_USB
    _usb_0_isr,
    _usb_1_isr,
    _usb_2_isr,
    _usb_3_isr,
#else
    0,
    0,
    0,
    0,
#endif
#ifdef ID_GMAC
    _gmac_isr,
#else
    0,
#endif
    _tcc0_0_isr,
    _tcc0_1_isr,
    _tcc0_2_isr,
    _tcc0_3_isr,
    _tcc0_4_isr,
    _tcc0_5_isr,
    _tcc0_6_isr,
    _tcc1_0_isr,
    _tcc1_1_isr,
    _tcc1_2_isr,
    _tcc1_3_isr,
    _tcc1_4_isr,
    _tcc2_0_isr,
    _tcc2_1_isr,
    _tcc2_2_isr,
    _tcc2_3_isr,
#ifdef ID_TCC3
    _tcc3_0_isr,
    _tcc3_1_isr,
    _tcc3_2_isr,
#else
    0,
    0,
    0,
#endif
#ifdef ID_TCC4
    _tcc4_0_isr,
    _tcc4_1_isr,
    _tcc4_2_isr,
#else
    0,
    0,
    0,
#endif
    _tc0_isr,
    _tc1_isr,
    _tc2_isr,
    _tc3_isr,
#ifdef ID_TC4
    _tc4_isr,
#else
    0,
#endif
#ifdef ID_TC5
    _tc5_isr,
#else
    0,
#endif
#ifdef ID_TC6
    _tc6_isr,
#else
    0,
#endif
#ifdef ID_TC7
    _tc7_isr,
#else
    0,
#endif
    _pdec_0_isr,
    _pdec_1_isr,
    _pdec_2_isr,
    _adc0_0_isr,
    _adc0_1_isr,
    _adc1_0_isr,
    _adc1_1_isr,
    _ac_isr,
    _dac_0_isr,
    _dac_1_isr,
    _dac_2_isr,
    _dac_3_isr,
    _dac_4_isr,
#ifdef ID_I2S
    _i2s_isr,
#else
    0,
#endif
    _pcc_isr,
    _aes_isr,
    _trng_isr,
#ifdef ID_ICM
    _icm_isr,
#else
    0,
#endif
#ifdef ID_PUKCC
    _pukcc_isr,
#else
    0,
#endif
    _qspi_isr,
#ifdef ID_SDHC0
    _sdhc0_isr,
#else
    0,
#endif
#ifdef ID_SDHC1
    _sdhc1_isr
#else
    0
#endif
};