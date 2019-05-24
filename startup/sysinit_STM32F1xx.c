
#include <mcuconfig.h>


#define _USE_HAL_RCC    0


uint32_t SystemCoreClock         = 72000000U;        /*!< System Clock Frequency (Core Clock) */

const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};
const uint8_t APBPrescTable[8] =  {0, 0, 0, 0, 1, 2, 3, 4};


#if !defined(_USE_HAL_RCC) || _USE_HAL_RCC==0

/*------------------------------------------------------------
                      把所有时钟寄存器复位
------------------------------------------------------------*/
static void RCC_DeInit(void)
{
	RCC->APB2RSTR = 0x00000000;//外设复位
	RCC->APB1RSTR = 0x00000000;   	  
  	RCC->AHBENR = 0x00000014;  //flash时钟,闪存时钟使能.DMA时钟关闭
  	RCC->APB2ENR = 0x00000000; //外设时钟关闭.
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE
	RCC->CIR = 0x00000000;     //关闭所有中断
}


/*------------------------------------------------------------
                  外部8M,则得到72M的系统时钟
------------------------------------------------------------*/	
static void Stm32_Clock_Init(void)
{
	unsigned char temp=0;
	uint8_t timeout=0;
	RCC_DeInit();
	RCC->CR|=0x00010000;  //外部高速时钟使能HSEON

	timeout=0;
	while(!(RCC->CR>>17)&&timeout<200)timeout++;//等待外部时钟就绪

	//0-24M 等待0;24-48M 等待1;48-72M等待2;(非常重要!)
	FLASH->ACR|=0x32;//FLASH 2个延时周期

	RCC->CFGR|=0X001D0400;//APB1=DIV2;APB2=DIV1;AHB=DIV1;PLL=9*CLK;HSE作为PLL时钟源
	RCC->CR|=0x01000000;  //PLLON

	timeout=0;
	while(!(RCC->CR>>25)&&timeout<200)timeout++;//等待PLL锁定

	RCC->CFGR|=0x00000002;//PLL作为系统时钟
	while(temp!=0x02&&timeout<200)     //等待PLL作为系统时钟设置成功
	{   
		temp=RCC->CFGR>>2;
		timeout++;
		temp&=0x03;
	}
}


#else /* !defined(_USE_HAL_RCC) || _USE_HAL_RCC==0 */

static void Stm32_Clock_Init(void)
{
	RCC_ClkInitTypeDef clkinitstruct = {0};
	RCC_OscInitTypeDef oscinitstruct = {0};

	HAL_RCC_DeInit();

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	oscinitstruct.OscillatorType  = RCC_OSCILLATORTYPE_HSE;
	oscinitstruct.HSEState        = RCC_HSE_ON;
	oscinitstruct.HSEPredivValue  = RCC_HSE_PREDIV_DIV2;
	oscinitstruct.PLL.PLLState    = RCC_PLL_ON;
	oscinitstruct.PLL.PLLSource   = RCC_PLLSOURCE_HSE;
	oscinitstruct.PLL.PLLMUL      = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&oscinitstruct)!= HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
		clocks dividers */
	clkinitstruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	clkinitstruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clkinitstruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clkinitstruct.APB2CLKDivider = RCC_HCLK_DIV1;
	clkinitstruct.APB1CLKDivider = RCC_HCLK_DIV2;
	if (HAL_RCC_ClockConfig(&clkinitstruct, FLASH_LATENCY_0)!= HAL_OK)
	{
		/* Initialization Error */
		while(1);
	}
}
#endif /* !defined(_USE_HAL_RCC) || _USE_HAL_RCC==0 */


void _init()
{
	Stm32_Clock_Init();
    HAL_Init();
}


void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

