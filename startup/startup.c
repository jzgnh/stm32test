

extern void _estack();

extern void Reset_Handler();

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


void WWDG_IRQHandler()              __attribute__ ((weak, alias("NMI_Handler")));
void PVD_IRQHandler()               __attribute__ ((weak, alias("NMI_Handler")));
void TAMPER_IRQHandler()            __attribute__ ((weak, alias("NMI_Handler")));
void RTC_IRQHandler()               __attribute__ ((weak, alias("NMI_Handler")));
void FLASH_IRQHandler()             __attribute__ ((weak, alias("NMI_Handler")));
void RCC_IRQHandler()               __attribute__ ((weak, alias("NMI_Handler")));
void EXTI0_IRQHandler()             __attribute__ ((weak, alias("NMI_Handler")));
void EXTI1_IRQHandler()             __attribute__ ((weak, alias("NMI_Handler")));
void EXTI2_IRQHandler()             __attribute__ ((weak, alias("NMI_Handler")));
void EXTI3_IRQHandler()             __attribute__ ((weak, alias("NMI_Handler")));
void EXTI4_IRQHandler()             __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel1_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel2_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel3_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel4_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel5_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel6_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void DMA1_Channel7_IRQHandler()     __attribute__ ((weak, alias("NMI_Handler")));
void ADC1_2_IRQHandler()            __attribute__ ((weak, alias("NMI_Handler")));
void USB_HP_CAN1_TX_IRQHandler()    __attribute__ ((weak, alias("NMI_Handler")));
void USB_LP_CAN1_RX0_IRQHandler()   __attribute__ ((weak, alias("NMI_Handler")));
void CAN1_RX1_IRQHandler()          __attribute__ ((weak, alias("NMI_Handler")));
void CAN1_SCE_IRQHandler()          __attribute__ ((weak, alias("NMI_Handler")));
void EXTI9_5_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void TIM1_BRK_IRQHandler()          __attribute__ ((weak, alias("NMI_Handler")));
void TIM1_UP_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void TIM1_TRG_COM_IRQHandler()      __attribute__ ((weak, alias("NMI_Handler")));
void TIM1_CC_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void TIM2_IRQHandler()              __attribute__ ((weak, alias("NMI_Handler")));
void TIM3_IRQHandler()              __attribute__ ((weak, alias("NMI_Handler")));
void TIM4_IRQHandler()              __attribute__ ((weak, alias("NMI_Handler")));
void I2C1_EV_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void I2C1_ER_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void I2C2_EV_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void I2C2_ER_IRQHandler()           __attribute__ ((weak, alias("NMI_Handler")));
void SPI1_IRQHandler()              __attribute__ ((weak, alias("NMI_Handler")));
void SPI2_IRQHandler()              __attribute__ ((weak, alias("NMI_Handler")));
void USART1_IRQHandler()            __attribute__ ((weak, alias("NMI_Handler")));
void USART2_IRQHandler()            __attribute__ ((weak, alias("NMI_Handler")));
void USART3_IRQHandler()            __attribute__ ((weak, alias("NMI_Handler")));
void EXTI15_10_IRQHandler()         __attribute__ ((weak, alias("NMI_Handler")));
void RTCAlarm_IRQHandler()          __attribute__ ((weak, alias("NMI_Handler")));
void USBWakeUp_IRQHandler()         __attribute__ ((weak, alias("NMI_Handler")));


void _exit()         __attribute__ ((weak, alias("NMI_Handler")));

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

    // External Interrupts
    WWDG_IRQHandler,            // Window Watchdog
    PVD_IRQHandler,             // PVD through EXTI Line detect
    TAMPER_IRQHandler,          // Tamper
    RTC_IRQHandler,             // RTC
    FLASH_IRQHandler,           // Flash
    RCC_IRQHandler,             // RCC
    EXTI0_IRQHandler,           // EXTI Line 0
    EXTI1_IRQHandler,           // EXTI Line 1
    EXTI2_IRQHandler,           // EXTI Line 2
    EXTI3_IRQHandler,           // EXTI Line 3
    EXTI4_IRQHandler,           // EXTI Line 4
    DMA1_Channel1_IRQHandler,   // DMA1 Channel 1
    DMA1_Channel2_IRQHandler,   // DMA1 Channel 2
    DMA1_Channel3_IRQHandler,   // DMA1 Channel 3
    DMA1_Channel4_IRQHandler,   // DMA1 Channel 4
    DMA1_Channel5_IRQHandler,   // DMA1 Channel 5
    DMA1_Channel6_IRQHandler,   // DMA1 Channel 6
    DMA1_Channel7_IRQHandler,   // DMA1 Channel 7
    ADC1_2_IRQHandler,          // ADC1_2
    USB_HP_CAN1_TX_IRQHandler,  // USB High Priority or CAN1 TX
    USB_LP_CAN1_RX0_IRQHandler, // USB Low  Priority or CAN1 RX0
    CAN1_RX1_IRQHandler,        // CAN1 RX1
    CAN1_SCE_IRQHandler,        // CAN1 SCE
    EXTI9_5_IRQHandler,         // EXTI Line 9..5
    TIM1_BRK_IRQHandler,        // TIM1 Break
    TIM1_UP_IRQHandler,         // TIM1 Update
    TIM1_TRG_COM_IRQHandler,    // TIM1 Trigger and Commutation
    TIM1_CC_IRQHandler,         // TIM1 Capture Compare
    TIM2_IRQHandler,            // TIM2
    TIM3_IRQHandler,            // TIM3
    TIM4_IRQHandler,            // TIM4
    I2C1_EV_IRQHandler,         // I2C1 Event
    I2C1_ER_IRQHandler,         // I2C1 Error
    I2C2_EV_IRQHandler,         // I2C2 Event
    I2C2_ER_IRQHandler,         // I2C2 Error
    SPI1_IRQHandler,            // SPI1
    SPI2_IRQHandler,            // SPI2
    USART1_IRQHandler,          // USART1
    USART2_IRQHandler,          // USART2
    USART3_IRQHandler,          // USART3
    EXTI15_10_IRQHandler,       // EXTI Line 15..10
    RTCAlarm_IRQHandler,        // RTC Alarm through EXTI Line
    USBWakeUp_IRQHandler,       // USB Wakeup from suspend
};


