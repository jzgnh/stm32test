
#include "mcuconfig.h"

void HAL_MspInit(void)
{
	__HAL_RCC_AFIO_CLK_ENABLE();
	__HAL_RCC_PWR_CLK_ENABLE();

    __HAL_AFIO_REMAP_SWJ_NOJTAG();
}

#define USART_TX_PORT           _GENNAME(GPIO,STDIO_TX_GPIOPORT,__GENNAME_NONE)
#define USART_TX_PIN            _GENNAME(GPIO_PIN_,STDIO_TX_GPIO_PIN,__GENNAME_NONE)
#define USART_TX_ENABLE_CLK()   _GENNAME(__HAL_RCC_GPIO,STDIO_TX_GPIOPORT,_CLK_ENABLE)()


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    USART_TX_ENABLE_CLK();

    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Pin = USART_TX_PIN;
    HAL_GPIO_Init(USART_TX_PORT, &GPIO_InitStruct);
}


void LL_SPI_MSP_init(SPI_TypeDef *SPIx)
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

