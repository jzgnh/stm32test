
#include <stdio.h>
#include <stdlib.h>

#include "mcuconfig.h"

#ifndef STDIO_UARTx
#define STDIO_UARTx 1
#endif

#ifndef STDIO_TX_GPIOPORT
#define STDIO_TX_GPIOPORT   A
#endif

#define _CONSOLE_UART       _GENNAME(USART,STDIO_UARTx,__GENNAME_NONE)
#define _CONSOLE_IRQ        _GENNAME(USART,STDIO_UARTx,_IRQn)
#define _CONSOLE_UART_CLK_ENABLE()  do {    \
         _GENNAME(__HAL_RCC_GPIO,STDIO_TX_GPIOPORT,_CLK_ENABLE)(); \
         _GENNAME(__HAL_RCC_USART,STDIO_UARTx,_CLK_ENABLE)(); } while(0)


static UART_HandleTypeDef StdIOUart;

__attribute__ ((constructor))
static void _uart1_init()
{
    //trace_puts("initial uart");
    _CONSOLE_UART_CLK_ENABLE();

    StdIOUart.Instance        = _CONSOLE_UART;

    StdIOUart.Init.BaudRate = 115200;
    StdIOUart.Init.WordLength = UART_WORDLENGTH_8B;
    StdIOUart.Init.StopBits = UART_STOPBITS_1;
    StdIOUart.Init.Parity = UART_PARITY_NONE;
    StdIOUart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    StdIOUart.Init.OverSampling = UART_OVERSAMPLING_16;
    StdIOUart.Init.Mode = UART_MODE_TX;

    HAL_UART_Init(&StdIOUart);

    HAL_NVIC_DisableIRQ(_CONSOLE_IRQ);
}

__attribute__ ((destructor))
static void _uart1_fini()
{
}

////////////////////////////////////////////////////////////////

_IO_PUTCHAR_PROTOTYPE
{
    //trace_putc(c);

    while ( !__HAL_UART_GET_FLAG(&StdIOUart, UART_FLAG_TXE) );
    StdIOUart.Instance->DR = (uint32_t)c&0xFF;
    //HAL_UART_Transmit(&StdIOUart, (uint8_t*)&c, 1, HAL_MAX_DELAY);
    return (unsigned char)c;
}
