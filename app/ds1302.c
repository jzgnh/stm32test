
#include "app.h"

#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90
#define ds1302_clkburst_add		0xbe

//#define DSCLKPIN        GPIO_PIN_7
//#define DSCLKGPIOPORT   GPIOB

#define DSCLKPIN        GPIO_PIN_12
#define DSCLKGPIOPORT   GPIOA

#define DSDATAPIN       GPIO_PIN_5
#define DSDATAGPIOPORT  GPIOB

//#define DSRSTPIN        GPIO_PIN_15
//#define DSRSTGPIOPORT   GPIOA

#define DSRSTPIN        GPIO_PIN_7
#define DSRSTGPIOPORT   GPIOB

#define DS_ENABLE_CLK()    do { __HAL_RCC_GPIOB_CLK_ENABLE();   \
                                __HAL_RCC_GPIOA_CLK_ENABLE(); } while(0)

#define DS_RESET0()  HAL_GPIO_WritePin(DSRSTGPIOPORT, DSRSTPIN, GPIO_PIN_RESET)
#define DS_RESET1()  HAL_GPIO_WritePin(DSRSTGPIOPORT, DSRSTPIN, GPIO_PIN_SET)


#define DS_DATA0()   HAL_GPIO_WritePin(DSDATAGPIOPORT, DSDATAPIN, GPIO_PIN_RESET)
#define DS_DATA1()   HAL_GPIO_WritePin(DSDATAGPIOPORT, DSDATAPIN, GPIO_PIN_SET)

#define DS_GET_DATA()   HAL_GPIO_ReadPin(DSDATAGPIOPORT, DSDATAPIN)
#define DS_SET_DATA(v)  HAL_GPIO_WritePin(DSDATAGPIOPORT, DSDATAPIN, v)


#define DS_CLK0()    HAL_GPIO_WritePin(DSCLKGPIOPORT, DSCLKPIN, GPIO_PIN_RESET)
#define DS_CLK1()    HAL_GPIO_WritePin(DSCLKGPIOPORT, DSCLKPIN, GPIO_PIN_SET)


static unsigned char ds_getreg(unsigned char r);
static void ds_setreg(unsigned char r, unsigned char v);


static void ds_dataoutput(int yes_or_no) {
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Mode = yes_or_no ? GPIO_MODE_OUTPUT_PP : GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = yes_or_no ? GPIO_PULLUP : GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    GPIO_InitStruct.Pin = DSDATAPIN;
    HAL_GPIO_Init(DSDATAGPIOPORT, &GPIO_InitStruct);
}

static unsigned int _delaytick = 0;

void DS_Init()
{
    GPIO_InitTypeDef  GPIO_InitStruct = {0};
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    DS_ENABLE_CLK();

    GPIO_InitStruct.Pin = DSCLKPIN;
    HAL_GPIO_Init(DSCLKGPIOPORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DSDATAPIN;
    HAL_GPIO_Init(DSDATAGPIOPORT, &GPIO_InitStruct);

    //GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Pin = DSRSTPIN;
    HAL_GPIO_Init(DSRSTGPIOPORT, &GPIO_InitStruct);

    DS_RESET0();
    DS_CLK0();

    _delaytick = 3; //(SystemCoreClock/1000/1000)>>2;   // 1.5 us
}
void DS_DeInit()
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;

    DS_ENABLE_CLK();

    GPIO_InitStruct.Pin = DSCLKPIN;
    HAL_GPIO_Init(DSCLKGPIOPORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DSDATAPIN;
    HAL_GPIO_Init(DSDATAGPIOPORT, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = DSRSTPIN;
    HAL_GPIO_Init(DSRSTGPIOPORT, &GPIO_InitStruct);
}


static void setprotect(int y_o_n) {
    ds_setreg(ds1302_control_add, y_o_n ? 0x80 : 0x00);
}

void DS_Get(TS_DATATypeDef *ts)
{
    ts->S = ds_getreg(ds1302_sec_add);
    ts->M = ds_getreg(ds1302_min_add);
    ts->H = ds_getreg(ds1302_hr_add);

    ts->d = ds_getreg(ds1302_date_add);
    ts->m = ds_getreg(ds1302_month_add);
    ts->y = ds_getreg(ds1302_year_add);

    ts->w = ds_getreg(ds1302_day_add);
}
void DS_Set(TS_DATATypeDef *ts)
{

    if (ts->H & 0x80) {
        ts->H &= ~0x80;
        if (ts->H & 1<<5) {
            if (ts->H&0x08)
                ts->H += 0x18;  // only 8,9 + 12
            else if (ts->H!=0x12)
                ts->H += 0x12;     // 0-7,10-11 + 12
        }
    }

    setprotect(0);

    ds_setreg(ds1302_sec_add, 0x80);
    return;

    ds_setreg(ds1302_year_add, ts->y);
    ds_setreg(ds1302_month_add, ts->m);
    ds_setreg(ds1302_date_add, ts->d);

    //ds_setreg(ds1302_day_add, ts->w&0x07);

    ds_setreg(ds1302_hr_add, ts->H);
    ds_setreg(ds1302_min_add, ts->M);
    ds_setreg(ds1302_sec_add, ts->S & 0x7F);  // start clock

    setprotect(1);
}



////////////////////////////////////////////

#define wait1()    do { for(volatile unsigned int __isf=0; __isf<_delaytick ;++__isf) ; } while(0)

static unsigned char ds_getreg(unsigned char r)
{
    unsigned char v;

    DS_RESET1();
    r |= 1;        // for read

    for (int i=0;i<8;++i) {
        DS_SET_DATA(r&0x01);
        wait1();
        DS_CLK1();
        r >>= 1;

        if (i==7) break;
        wait1();
        DS_CLK0();
    }

    ds_dataoutput(0);   // input
    wait1();
    v = 0;

    for (int i=0;i<8;++i) {
        DS_CLK0();
        wait1();
        v >>= 1;
        if (DS_GET_DATA())
            v |= 0x80;

        if (i==7) break;
        DS_CLK1();
        wait1();
    }
    wait1();
    DS_RESET0();
    ds_dataoutput(1);   // output

    return v;
}
static void ds_setreg(unsigned char r, unsigned char v)
{
    unsigned int s = v;

    s <<= 8;
    s |= r & ~1;    // for write

    DS_RESET1();

    for (int i=0;i<16;++i) {
        DS_SET_DATA(s&0x01);
        wait1();
        DS_CLK1();
        s >>= 1;

        wait1();
        DS_CLK0();
    }
    wait1();
    DS_RESET0();

    wait1();
    DS_DATA0();
}



