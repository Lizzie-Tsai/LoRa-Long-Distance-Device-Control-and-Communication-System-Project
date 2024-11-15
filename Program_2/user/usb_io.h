#ifndef _USB_IO_H_
#define _USB_IO_H_

#include "stm32f10x.h"
#include "usb_desc.h"
#include "usb_lib.h"

uint32_t USB_SendData(uint8_t bEpNum,uint8_t *data,uint32_t dataNum);
uint32_t USB_GetData(uint8_t bEpNum,uint8_t *data,uint32_t dataNum);
void USB_SendString(u8 *str);
#endif //_USB_IO_H_
