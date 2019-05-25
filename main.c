
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mcuconfig.h"


static const unsigned int numbits[] = {
	0x77, 0x14, 0xB3, 0xB6, 0xD4, 0xE6, 0xE7, 0x34,
	0xF7, 0xF6, 0xF5, 0xC7, 0x63, 0x97, 0xE3, 0xE1,
};


static char buf[] = "abcdef";

#if 1
#define LED_PIN             GPIO_PIN_12
#define LED_GPIO_PORT       GPIOB
#define LED_ENABLE_CLK()    __HAL_RCC_GPIOB_CLK_ENABLE()
#else
#define LED_PIN             GPIO_PIN_13
#define LED_GPIO_PORT       GPIOD
#define LED_ENABLE_CLK()    __HAL_RCC_GPIOD_CLK_ENABLE()
#endif

#define LED_Toggle()       HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN)


static void LED_Init()
{
    LED_ENABLE_CLK();

    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_SYSTICK_Callback(void)
{

}

int main()
{
	int i = 0;
	int ss = 0x08;

    LED_Init();
    

	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //GPIOA

	//GPIOA->CRL = 0x11111111;
	//GPIOA->ODR = 0x00000000;

	while (1) {

		HAL_Delay(200);
		LED_Toggle();

		HAL_Delay(200);
		LED_Toggle();

        //printf("curr: %d  %ld\n", i, HAL_GetTick());
        //fputs("111111111111111");
        //trace_puts("111111111111111");
        //trace_puts(buf);

		//GPIOA->ODR = (~numbits[i])  & (~ss);
		i += 1;
		i %= sizeof(numbits)/sizeof(numbits[0]);
		if (!i) ss ^= 0x08;
	}

    return 0;
}

