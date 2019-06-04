
#include "mcuconfig.h"

#if 0
#define USART_TX_AF         GPIO_AF7_USART2
#define USART_TX_PIN        GPIO_PIN_2
#define USART_RX_AF         GPIO_AF7_USART2
#define USART_RX_PIN        GPIO_PIN_3

#define USART_TX_PORT       GPIOA
#define USART_RX_PORT       GPIOA

#define USART_TX_ENABLE_CLK()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define USART_RX_ENABLE_CLK()

#else

#define USART_TX_PORT           _GENNAME(GPIO,STDIO_TX_GPIOPORT,__GENNAME_NONE)
#define USART_TX_PIN            _GENNAME(GPIO_PIN_,STDIO_TX_GPIO_PIN,__GENNAME_NONE)
#define USART_TX_ENABLE_CLK()   _GENNAME(__HAL_RCC_GPIO,STDIO_TX_GPIOPORT,_CLK_ENABLE)()

#endif


void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    USART_TX_ENABLE_CLK();

    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    GPIO_InitStruct.Alternate = USART_TX_AF;
    GPIO_InitStruct.Pin = USART_TX_PIN;
    HAL_GPIO_Init(USART_TX_PORT, &GPIO_InitStruct);

    /*
    GPIO_InitStruct.Alternate = USART_RX_AF;
    GPIO_InitStruct.Pin = USART_RX_PIN;
    HAL_GPIO_Init(USART_RX_PORT, &GPIO_InitStruct);
    // */
}



