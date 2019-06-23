
#include "mcuconfig.h"


void LL_MSP_init(SPI_TypeDef *SPIx)
{
    if (SPIx == SPI1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        GPIO_InitTypeDef  GPIO_InitStruct = {0};
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

        GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
}
