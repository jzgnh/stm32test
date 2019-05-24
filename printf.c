
#include <stdio.h>
#include <stdlib.h>

#include "mcuconfig.h"

#define _USA_HAL_UART       1

#if defined(_USA_HAL_UART) && _USA_HAL_UART!=0
static UART_HandleTypeDef StdIOUart;
#endif

__attribute__ ((constructor))
static void _uart1_init()
{
    trace_puts("initial uart");

#if defined(_USA_HAL_UART) && _USA_HAL_UART!=0
    __HAL_RCC_USART1_CLK_ENABLE();

    StdIOUart.Instance        = USART1;

    StdIOUart.Init.BaudRate   = 115200;
    StdIOUart.Init.WordLength = UART_WORDLENGTH_8B;
    StdIOUart.Init.StopBits   = UART_STOPBITS_1;
    StdIOUart.Init.Parity     = UART_PARITY_ODD;
    StdIOUart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
    StdIOUart.Init.Mode       = UART_MODE_TX;

    HAL_UART_Init(&StdIOUart);

#else
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN; //UART1
    SET_BIT(USART1->CR1, USART_CR1_UE);
    USART1->BRR = 0x0271;
    SET_BIT(USART1->CR1, USART_CR1_TE);
#endif
}

__attribute__ ((destructor))
static void _fini_uart1()
{
}

////////////////////////////////////////////////////////////////

int	fputc(int c, FILE *f)
{
#if defined(_USA_HAL_UART) && _USA_HAL_UART!=0
    trace_putc(c);
    //HAL_UART_Transmit(&StdIOUart, (uint8_t*)&c, 1, HAL_MAX_DELAY);
    HAL_UART_Transmit(&StdIOUart, (uint8_t*)&c, 1, 0);
#else
    while (!READ_BIT(USART1->SR, USART_SR_TXE));
    USART1->DR = (unsigned char)c;
#endif
    return (unsigned char)c;
}
