#include <sam.h>
#include <stdlib.h>
#include <stdio.h>
#include "atomic.h"

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
    // TODO:
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

    return 0;
}
int main()
{

    for(;;)
    {

    }

    return 0;
}