#include <sam.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug_macros.h"
#include "gclk.h"
#include "mclk.h"
#include "dbg.h"
#include "systick.h"
#include "utils.h"
#include "atomic.h"
#include "rtsc.h"
#include "port.h"

// Structs

// Forward declarations
static void reset() __attribute__((noreturn));
static void sleep();

static uint32_t get_free_ram();

static void get_device_name(char *pszDeviceName, uint32_t ulDeviceNameSize);
static uint8_t get_device_revision();

// Variables

// ISRs

// Functions
void reset()
{
    SCB->AIRCR = 0x05FA0000 | SCB_AIRCR_SYSRESETREQ_Msk;

    while(1);
}
void sleep()
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // Configure Deep Sleep (EM2/3)

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        __DMB(); // Wait for all memory transactions to finish before memory access
        __DSB(); // Wait for all memory transactions to finish before executing instructions
        __ISB(); // Wait for all memory transactions to finish before fetching instructions
        __SEV(); // Set the event flag to ensure the next WFE will be a NOP
        __WFE(); // NOP and clear the event flag
        __WFE(); // Wait for event
        __NOP(); // Prevent debugger crashes
    }
}

uint32_t get_free_ram()
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        extern void *_sbrk(int);

        void *pCurrentHeap = _sbrk(1);

        if(!pCurrentHeap)
            return 0;

        uint32_t ulFreeRAM = (uint32_t)__get_MSP() - (uint32_t)pCurrentHeap;

        _sbrk(-1);

        return ulFreeRAM;
    }
}

void get_device_name(char *pszDeviceName, uint32_t ulDeviceNameSize)
{
    // TODO:

    snprintf(pszDeviceName, ulDeviceNameSize, "ATSAME51J20");
}
uint8_t get_device_revision()
{
    // TODO:

    return 1;
}

int init()
{
    gclk_init();
    gclk_update_clocks();
    mclk_init();
    mclk_update_clocks();

    dbg_init(); // Init Debug module
    dbg_swo_config(BIT(0), 2000000); // Init SWO channel 0 at 6 MHz

    systick_init();

    port_init();

    char szDeviceName[32];

    get_device_name(szDeviceName, 32);

    DBGPRINT("\n\n");

    DBGPRINTLN_CTX("same5x-app v%lu (%s %s)!", BUILD_VERSION, __DATE__, __TIME__);
    DBGPRINTLN_CTX("Device: %s", szDeviceName);
    DBGPRINTLN_CTX("Device Revision: %hhu", get_device_revision());
    DBGPRINTLN_CTX("Free RAM: %lu KiB", get_free_ram() >> 10);

    DBGPRINTLN_CTX("RSTC - Reset cause: 0x%02X", rstc_get_reset_reason());

    for (uint8_t i = 0; i <= 11; i++)
    {
        DBGPRINTLN_CTX("GCLK - GCLK%hhu Clock: %.1f MHz", i, (float)GCLK_CLOCK_FREQ[i] / 1000000);
    }
    DBGPRINTLN_CTX("MCLK - HS APB Clock: %.1f MHz", (float)APB_HS_CLOCK_FREQ / 1000000);
    DBGPRINTLN_CTX("MCLK - CPU APB Clock: %.1f MHz", (float)APB_CPU_CLOCK_FREQ / 1000000);
    DBGPRINTLN_CTX("MCLK - CPU AHB Clock: %.1f MHz", (float)AHB_CPU_CLOCK_FREQ / 1000000);
    DBGPRINTLN_CTX("MCLK - CPU Clock: %.1f MHz", (float)CPU_CLOCK_FREQ / 1000000);




    return 0;
}
int main()
{
    DBGPRINTLN_CTX("OUT ptr: 0x%08X", (uint32_t)&(PORT->Group[0].DIRCLR.reg));

    for(;;)
    {
        delay_ms(5000);
    }

    return 0;
}