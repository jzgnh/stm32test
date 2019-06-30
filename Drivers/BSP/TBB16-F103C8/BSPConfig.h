
#define STM32F103xB

#define USE_HAL_DRIVER

#define LED_PIN             GPIO_PIN_12
#define LED_GPIO_PORT       GPIOB
#define LED_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define STDIO_UARTx         1
#define STDIO_TX_GPIOPORT   A

#define STDIO_TX_GPIO_PIN   9
