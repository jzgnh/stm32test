
#include "mcuconfig.h"

extern unsigned int __etext;
extern unsigned int __data_start__;
extern const unsigned int __data_end__;

extern unsigned int __bss_start__;
extern const unsigned int __bss_end__;

extern void (*__initf_start[])(void);
extern void (*__initf_end[])(void);

extern void (*__finif_start[])(void);
extern void (*__finif_end[])(void);


__weak
void _preinit()
{
}

__weak
void _init()
{
}

void __libc_init_array()
{
    
    for (unsigned int *p=&__bss_start__; p<&__bss_end__ ; ++p)
        *p = 0;

    for (unsigned int *i=&__data_start__, *j=&__etext; i<&__data_end__ ; ++i, ++j)
        *i = *j;

    _preinit();

    do {
        int c = __initf_end - __initf_start;
        for (int i=0; i<c ; ++i)
            if (__initf_start[i]) (__initf_start[i])();
    } while(0);


    _init();
}


void __libc_final_array()
{
    int c = __finif_end - __finif_start;
    for (int i=0; i<c ; ++i)
        if (__finif_start[i]) (__finif_start[i])();
}

extern void main();

__attribute__ ((naked,weak))
void Reset_Handler()
{
    __libc_init_array();
    main();
    __libc_final_array();
    while(1);
}
