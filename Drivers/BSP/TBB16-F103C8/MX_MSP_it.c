
#include "mcuconfig.h"

#include <stdio.h>


extern PCD_HandleTypeDef PCD0;


void USB_HP_CAN1_TX_IRQHandler()
{
    HAL_PCD_IRQHandler(&PCD0);
}

void USB_LP_CAN1_RX0_IRQHandler()
{
    HAL_PCD_IRQHandler(&PCD0);
}

void USBWakeUp_IRQHandler()
{
    HAL_PCD_IRQHandler(&PCD0);
}
