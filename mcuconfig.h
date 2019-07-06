

#include <stdint.h>

#ifdef _MMOS_STM32F1xx
#include <stm32f1xx.h>
#include <stm32f1xx_hal_conf.h>

#include <stm32f1xx_ll_bus.h>
#include <stm32f1xx_ll_rcc.h>
#include <stm32f1xx_ll_spi.h>

#include <stm32f1xx_ll_usb.h>

#define _IO_PUTCHAR_PROTOTYPE int __io_putchar(int c)
#endif

#ifdef _MMOS_STM32F4xx
#include <stm32f4xx.h>
#include <stm32f4xx_hal_conf.h>

#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_rcc.h>
#include <stm32f4xx_ll_spi.h>

#include <stm32f4xx_ll_usb.h>

#define _IO_PUTCHAR_PROTOTYPE int __swbuf_r(struct _reent *reent, int c, FILE *f)
#endif

int trace_putc(int c);
int trace_puts(const char *s);


#define __GENNAME_NONE

#define __GENNAME(f1,f2,f3) f1##f2##f3
#define _GENNAME(f1,f2,f3)  __GENNAME(f1,f2,f3)

void log_adds(const char *s);
void log_adds0(const char *s);
void log_addc(char c);

void log_data(void *d, int sz);

int log_getc();
int log_ugetc(int c);
