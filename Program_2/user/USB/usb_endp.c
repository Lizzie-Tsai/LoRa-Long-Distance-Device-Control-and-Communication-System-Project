/******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
* File Name          : usb_endp.c
* Author             : MCD Application Team
* Version            : V3.3.0
* Date               : 21-March-2011
* Description        : Endpoint routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifdef STM32L1XX_MD
#include "stm32l1xx.h"
#else
#include "stm32f10x.h"
#endif /* STM32L1XX_MD */

#include "platform_config.h"
#include "usb_lib.h"
#include "usb_istr.h"
#include "usb_desc.h"
//#include "stm32_eval.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : EP1_OUT_Callback.
* Description    : EP1 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
volatile uint32_t EP1_ReceivedCount=0;
uint8_t USB_Receive_Buffer[EP_SIZE];
uint8_t USB_Send_Buffer[EP_SIZE];


void EP1_OUT_Callback(void)
{

	EP1_ReceivedCount = GetEPRxCount(ENDP1);
	PMAToUserBufferCopy(USB_Receive_Buffer, ENDP1_RXADDR, EP1_ReceivedCount);

	SetEPRxStatus(ENDP1, EP_RX_VALID);
 
#ifndef STM32F10X_CL   
  //SetEPRxStatus(ENDP1, EP_RX_VALID);
#endif /* STM32F10X_CL */
 
}

/*******************************************************************************
* Function Name  : EP1_IN_Callback.
* Description    : EP1 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

void EP2_IN_Callback(void)
{
    // u8 ii;
	//printf("Send Data to PC\r\n");
     //for (ii=0;ii<64;ii++) USB_Send_Buffer[ii] = 0x00;
     //for LED test
    // if (GPIOA->ODR & 0x0c )  GPIOA->ODR &= (~0x0c);
    // else GPIOA->ODR |= 0x0c;
}

// void EP1_IN_Callback(void)
// {
// 	printf("EP1_IN_Callback\r\n");
// }
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

