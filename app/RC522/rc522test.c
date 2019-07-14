

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"


#include "rc522.h"



int rc522_main()
{
    int i = 0;

    uint16_t sl;
    uint8_t str[MFRC522_MAX_LEN];

    uint32_t tick = HAL_GetTick();
    uint32_t ntick;

    puts("begin mfrc522...\n");

    MFRC522_Init();

    ntick = tick + 20;
    while(1) {
        //if ((i=log_getc())>0)
        //    putchar(i);

        puts("REQA 26");
        sl = 0;
        if (MFRC522_Request(PICC_REQIDL, str)) {
            i = MFRC522_GetVersion();
            printf("    %02X\n", i);
            continue;
        }


        // puts("REQA 26");
        printf("ATQA %02X %02X %02X %02X\n",
                    str[0], str[1], str[2], str[3]);


    }
}
