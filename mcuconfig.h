

#include <stdint.h>

#ifdef _MMOS_STM32F1xx
#include <stm32f1xx.h>
#include <stm32f1xx_hal_rcc.h>
#include <stm32f1xx_hal_dma.h>
#include <stm32f1xx_hal_uart.h>
#include <stm32f1xx_hal_gpio.h>
#endif

#ifdef _MMOS_STM32F4xx
#include <stm32f4xx.h>
#include <stm32f4xx_hal_rcc.h>
#include <stm32f4xx_hal_dma.h>
#include <stm32f4xx_hal_uart.h>
#include <stm32f4xx_hal_gpio.h>
#endif

int trace_putc(int c);
int trace_puts(const char *s);

#ifndef GPIO_SPEED_FAST
#define GPIO_SPEED_FAST GPIO_SPEED_FREQ_HIGH
#endif
