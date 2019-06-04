

#define STM32F407xx
#define USE_HAL_DRIVER

#define LED_PIN             GPIO_PIN_0
#define LED_GPIO_PORT       GPIOC
#define LED_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()

#define STDIO_UARTx         1
#define STDIO_TX_GPIOPORT   A

#define STDIO_TX_GPIO_PIN   9
#define USART_TX_AF         GPIO_AF7_USART1


