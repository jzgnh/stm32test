
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"


static const unsigned int numbits[] = {
	0x77, 0x14, 0xB3, 0xB6, 0xD4, 0xE6, 0xE7, 0x34,
	0xF7, 0xF6, 0xF5, 0xC7, 0x63, 0x97, 0xE3, 0xE1,
};


static char buf[] = "abcdef";

#ifndef LED_PIN
#define LED_PIN        GPIO_PIN_12
#endif

#ifndef LED_GPIO_PORT
#define LED_GPIO_PORT       GPIOB
#endif

#ifndef LED_CLK_ENABLE
#define LED_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#endif


#define LED_Toggle()       HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_PIN)


static void LED_Init()
{
    LED_CLK_ENABLE();

    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);
}

void HAL_SYSTICK_Callback(void)
{

}

static const char *const weekday[] = {
	"ERR", "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN",
};

#define WeekDay(i)  (weekday[i&0x07])


int main()
{
	int i = 0;
	int ss = 0x08;



    LED_Init();

	/*
	TS_DATATypeDef tsdata;
	DS_Init();

	tsdata.y = 0x19;
	tsdata.m = 0x05;
	tsdata.d = 0x31;

	tsdata.H = 0x00;
	tsdata.M = 0x18;
	tsdata.S = 0x10;

	tsdata.w = 5;

	DS_Set(&tsdata);
	// */

	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; //GPIOA

	//GPIOA->CRL = 0x11111111;
	//GPIOA->ODR = 0x00000000;

	while (1) {

		HAL_Delay(180);
		LED_Toggle();

		//printf(" ");

		HAL_Delay(200);
		//LED_Toggle();

		/*
		DS_Get(&tsdata);
        printf("TIME: %02X-%02X-%02X %02X:%02X:%02X %s\n",
				tsdata.y, tsdata.m, tsdata.d,
				tsdata.H, tsdata.M, tsdata.S,
				WeekDay(tsdata.w));
		// */
        printf("curr: %d  %ld\n", i, HAL_GetTick());
		//puts(" ");
		//printf("C");
        //trace_puts("111111111111111");
        //trace_puts(buf);

		//GPIOA->ODR = (~numbits[i])  & (~ss);
		i += 1;
		i %= sizeof(numbits)/sizeof(numbits[0]);
		if (!i) ss ^= 0x08;
	}

    return 0;
}

