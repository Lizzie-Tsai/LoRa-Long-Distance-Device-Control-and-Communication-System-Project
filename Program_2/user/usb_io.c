#include "main.h"
#include "usb_io.h"

extern uint8_t USB_Receive_Buffer[EP_SIZE];
extern uint8_t USB_Send_Buffer[EP_SIZE];

void USB_SendString(u8 *str)
{
     u8 ii=0;   
     while(1)
     {
			
         USB_Send_Buffer[ii++]=*(str++);
         if (ii == EP_SIZE) break;
			 	
     }
     UserToPMABufferCopy(USB_Send_Buffer, ENDP2_TXADDR, EP_SIZE);
		 SetEPTxCount(EP_SIZE, ENDP2);
		 SetEPTxValid(ENDP2);
		LEDToggle();
}


uint32_t USB_SendData(uint8_t bEpNum,uint8_t *data,uint32_t dataNum)
{
	UserToPMABufferCopy(data, ENDP1_TXADDR, dataNum);
	SetEPTxCount(bEpNum, dataNum);
	SetEPTxValid(bEpNum);
	return dataNum;  
}
uint32_t USB_GetData(uint8_t bEpNum,uint8_t *data,uint32_t dataNum)
{
    uint32_t len=0;
	if(dataNum>sizeof(USB_Receive_Buffer)){
		dataNum = sizeof(USB_Receive_Buffer);
	}
	for(len=0;len<dataNum;len++){
		*data=USB_Receive_Buffer[len];
		data++;
	}
    return dataNum;
}
