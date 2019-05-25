

#include <mcuconfig.h>

extern void _estack();


extern unsigned int _sidata;
extern unsigned int _sdata;
extern const unsigned int _edata;

extern unsigned int _sbss;
extern const unsigned int _ebss;

extern void SystemInit();
extern void __libc_init_array();
extern void main();

__attribute__ ((weak))
void Reset_Handler()
{
    for (unsigned int *p=&_sbss; p<&_ebss; ++p)
        *p = 0;

    for (unsigned int *i=&_sdata, *j=&_sidata; i<&_edata; ++i, ++j)
        *i = *j;

    SystemInit();
    __libc_init_array();
    main();
    while(1);
}

__attribute__ ((naked,weak))
void NMI_Handler() { __asm__("B ."); }

void HardFault_Handler()        __attribute__ ((weak, alias("NMI_Handler")));
void MemManage_Handler()        __attribute__ ((weak, alias("NMI_Handler")));
void BusFault_Handler()         __attribute__ ((weak, alias("NMI_Handler")));
void UsageFault_Handler()       __attribute__ ((weak, alias("NMI_Handler")));
void SVC_Handler()              __attribute__ ((weak, alias("NMI_Handler")));
void DebugMon_Handler()         __attribute__ ((weak, alias("NMI_Handler")));
void PendSV_Handler()           __attribute__ ((weak, alias("NMI_Handler")));
void SysTick_Handler()          __attribute__ ((weak, alias("NMI_Handler")));


static void const *const isvectors[256] __attribute__ ((section(".isr_vector"),used)) =
{                                                           
    _estack,                    // Top of Stack
    Reset_Handler,              // Reset Handler
    NMI_Handler,                // NMI Handler
    HardFault_Handler,          // Hard Fault Handler
    MemManage_Handler,          // MPU Fault Handler
    BusFault_Handler,           // Bus Fault Handler
    UsageFault_Handler,         // Usage Fault Handler
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    SVC_Handler,                // SVCall Handler
    DebugMon_Handler,           // Debug Monitor Handler
    0,                          // Reserved
    PendSV_Handler,             // PendSV Handler
    SysTick_Handler,            // SysTick Handler

	// Only Cortex-M's basic interrupt handle
};


