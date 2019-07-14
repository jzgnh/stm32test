
#include "mcuconfig.h"

#include <stdio.h>


extern PCD_HandleTypeDef hpcd_USB_FS;


void USB_LP_CAN1_RX0_IRQHandler()
{
    // HAL_PCD_IRQHandler(&hpcd_USB_FS);
}

