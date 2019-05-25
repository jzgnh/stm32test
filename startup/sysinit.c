
#include <mcuconfig.h>


uint32_t SystemCoreClock         = HSI_VALUE;

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8] =  {0, 0, 0, 0, 1, 2, 3, 4};



void SystemInit()
{
    HAL_Init();
}


void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
