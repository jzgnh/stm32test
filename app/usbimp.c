
#include "app.h"

#include "usbd_def.h"

#define USBInst     USB

__weak
extern void LL_USB_MSP_init(USB_TypeDef *USBx)
{ }

void HAL_PCD_MspInit(PCD_HandleTypeDef* pcdHandle)
{
    LL_USB_MSP_init(USBInst);

    //HAL_NVIC_SetPriority(USB_HP_CAN1_TX_IRQn, 0, 0);
    HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 0, 0);
    //HAL_NVIC_SetPriority(USBWakeUp_IRQn, 1, 0);
    //HAL_NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
    HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    //HAL_NVIC_EnableIRQ(USBWakeUp_IRQn);
}

PCD_HandleTypeDef PCD0 = {0};

void USBInit()
{

    PCD0.Instance = USBInst;
    PCD0.Init.dev_endpoints = 8;
    PCD0.Init.speed = PCD_SPEED_FULL;
    PCD0.Init.ep0_mps = DEP0CTL_MPS_8;
    PCD0.Init.low_power_enable = DISABLE;
    PCD0.Init.lpm_enable = DISABLE;
    PCD0.Init.battery_charging_enable = DISABLE;

    HAL_PCD_Init(&PCD0);

    HAL_PCDEx_PMAConfig(&PCD0, 0x00, PCD_SNG_BUF, 0x20);
    HAL_PCDEx_PMAConfig(&PCD0, 0x80, PCD_SNG_BUF, 0x60);

#if 0
    HAL_PCDEx_PMAConfig(&PCD0, 0x81, PCD_SNG_BUF, 0xC0);
    HAL_PCDEx_PMAConfig(&PCD0, 0x01, PCD_SNG_BUF, 0x110);
    HAL_PCDEx_PMAConfig(&PCD0, 0x82, PCD_SNG_BUF, 0x100);
#endif


    HAL_PCD_Start(&PCD0);

    USBInst->CNTR &= ~USB_CNTR_SOFM;
    return;
}

void appendchar(const char c);
void appendstr(const char *s);
void appendstr0(const char *s);

void outdata(void *d, int sz)
{
    static const uint8_t digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    uint8_t *sdata = (uint8_t*)d;
    for (int i=0;i<sz;++i) {
        appendchar(digits[sdata[i]>>4]);
        appendchar(digits[sdata[i]&0x0f]);
        appendchar(' ');
    }
    appendchar('\n');
}

__ALIGN_BEGIN uint8_t USBD_FS_DeviceDesc[USB_LEN_DEV_DESC] __ALIGN_END =
{
    USB_LEN_DEV_DESC,                       /*bLength */
    USB_DESC_TYPE_DEVICE,       /*bDescriptorType*/
    0x00,                       /* bcdUSB */
    0x02,
    0x00,                        /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x20,                       /*bMaxPacketSize*/
    0x01, 0x1D,                 /*idVendor*/
    0x01, 0x10,                 /*idVendor*/
    0x00, 0x02,                 /*bcdDevice rel. 2.00*/
    1,                          /*Index of manufacturer  string*/
    2,                          /*Index of product string*/
    3,                          /*Index of serial number string*/
    1                           /*bNumConfigurations*/
};

__ALIGN_BEGIN uint8_t USBD_FS_ConfigDesc[] __ALIGN_END =
{
    USB_LEN_CFG_DESC,
    USB_DESC_TYPE_CONFIGURATION,
    USB_LEN_CFG_DESC + USB_LEN_IF_DESC, 0x00,   // wTotalLength
    1,                          // bNumInterfaces
    1,                          // bConfigurationValue
    0,                          // iConfiguration
    0,                          // bmAttributes
    49,                         // bMaxPower   98mA

    // interface
    USB_LEN_IF_DESC,
    USB_DESC_TYPE_INTERFACE,
    0,                          // bInterfaceNumber
    1,                          // bAlternateSetting
    0,                          // bNumEndpoints
    0xFF,                       // bInterfaceClass
    0xFF,                       // bInterfaceSubClass
    0xFF,                       // bInterfaceProtocol
    0,                          // iInterface
};

void HAL_PCD_DataOutStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    appendstr(__FUNCTION__);
}
void HAL_PCD_DataInStageCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    appendstr(__FUNCTION__);
    PCD_SET_EP_TX_STATUS(USB, 0, USB_EP_TX_VALID);
}
void HAL_PCD_SetupStageCallback(PCD_HandleTypeDef *hpcd)
{
    appendstr(__FUNCTION__);

    uint8_t *sdata = (uint8_t *)hpcd->Setup;
    outdata(sdata, 8);

    switch (sdata[1])
    {
    case USB_REQ_SET_ADDRESS: {           /* SET_ADDRESS */
        HAL_PCD_SetAddress(&PCD0, sdata[2]);
        HAL_PCD_EP_Transmit(&PCD0, 0, NULL, 0);
    }
    return;

    case USB_REQ_GET_DESCRIPTOR: {         /* GET_DESCRIPTOR */
        switch(sdata[3]) {
        case USB_DESC_TYPE_DEVICE:
            if(sdata[2]==0x00) {
                HAL_PCD_EP_Transmit(&PCD0, 0,
                        USBD_FS_DeviceDesc, MIN(USB_LEN_DEV_DESC, sdata[6]));

                outdata(USBD_FS_DeviceDesc, MIN(USB_LEN_DEV_DESC, sdata[6]));
            }
            break;
        case USB_DESC_TYPE_STRING: {
            uint8_t *pp = NULL;
            if (sdata[2]==0x01) {
                pp = (uint8_t*)("\x0E\x03" "C\0D\0G\0S\0 \0U");
            }
            else if (sdata[2]==0x02) {
                pp = (uint8_t*)("\x0E\x03" "M\0Y\0 \0D\0E\0V");
            }
            else if (sdata[2]==0x03) {
                pp = (uint8_t*)("\x20\x03" "1\x002\x003\x004\x005\x006\x007\x008\x009\x000\x00A\x00B\x00C\x00D\x00E\x00f");
            }

            if (pp && pp[0]>0) {
                HAL_PCD_EP_Transmit(&PCD0, 0, pp, MIN(pp[0], sdata[6]));
                outdata(pp, MIN(pp[0], sdata[6]));
            }
        }
        break;
        case USB_DESC_TYPE_CONFIGURATION: {
            HAL_PCD_EP_Transmit(&PCD0, 0,
                        USBD_FS_ConfigDesc, MIN(sizeof(USBD_FS_ConfigDesc), sdata[6]));

                outdata(USBD_FS_ConfigDesc, MIN(sizeof(USBD_FS_ConfigDesc), sdata[6]));
                break;
            }
            break;
        default: break;
        }
    }
    return;

    case USB_REQ_SET_CONFIGURATION: {
        HAL_PCD_EP_Transmit(&PCD0, 0, NULL, 0);
    }
    return;

    case USB_REQ_GET_CONFIGURATION: {
        HAL_PCD_EP_Transmit(&PCD0, 0, (uint8_t*)"\x01", 1);
    }
    return;


    default:
        break;
    }

    // HAL_PCD_EP_Transmit()
}
void HAL_PCD_SOFCallback(PCD_HandleTypeDef *hpcd)
{
    //appendstr(__FUNCTION__);
}
void HAL_PCD_ResetCallback(PCD_HandleTypeDef *hpcd)
{
    appendstr(__FUNCTION__);
    HAL_PCD_EP_Open(&PCD0, 0x00, 0x20, EP_TYPE_CTRL);
    HAL_PCD_EP_Open(&PCD0, 0x80, 0x20, EP_TYPE_CTRL);
}
void HAL_PCD_SuspendCallback(PCD_HandleTypeDef *hpcd)
{
    appendstr(__FUNCTION__);
}
void HAL_PCD_ResumeCallback(PCD_HandleTypeDef *hpcd)
{
    appendstr(__FUNCTION__);
}
void HAL_PCD_ISOOUTIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    appendstr(__FUNCTION__);
}
void HAL_PCD_ISOINIncompleteCallback(PCD_HandleTypeDef *hpcd, uint8_t epnum)
{
    appendstr(__FUNCTION__);
}
void HAL_PCD_ConnectCallback(PCD_HandleTypeDef *hpcd)
{
    appendstr(__FUNCTION__);
}
void HAL_PCD_DisconnectCallback(PCD_HandleTypeDef *hpcd)
{
    appendstr(__FUNCTION__);
}
