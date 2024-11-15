
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _USART_H
#define _USART_H
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stm32f10x.h>

/* Exported Functions --------------------------------------------------------*/
void USART_RCC_Configuration(void);
void USART_GPIO_Configuration(void);
void USART_Configuration(void);

#define __DEBUG__  

#ifdef __DEBUG__  
#define DEBUG(format,...) printf(""format"",##__VA_ARGS__)  
#else  

#define DEBUG(format,...)   
#endif  	

#define IMU_CMD 0x1A
#define BATTERY_CMD 0x1B
#define INTERRUPT_CMD 0x1C
#define READ_INPUT_CMD 0x1D



enum COMMAND_TYPE
{
		 CONNECT=66,										//�B��
     ACK_CONNECT,										//�B����ACK
     DISCONNECT,        						//�x��
		 SET_12V_RELAY,
		 ACK_12V_RELAY, 	
		 SET_110V_RELAY,
		 ACK_110V_RELAY, 	
		 SET_3V3_TRIGGER,
		 ACK_3V3_TRIGGER,
		 GET_ADC,
		 ACK_GET_ADC,	
		 SET_VOLTAGE,
		 ACK_SET_VOLTAGE,	
		 SET_PID_110V_RELAY,
		 ACK_PID_110V_RELAY, 	
		 SET_PID_3V3_TRIGGER,
		 ACK_PID_3V3_TRIGGER,
		 GET_TEMP,
		 ACK_GET_TEMP,
		 SET_LED,
	
     WRITE_SN,											//������̖
     ACK_WRITE_SN,									//������̖��ACK     
     WRITE_CPU_ID,									//����CPU ID
     ACK_WRITE_CPU_ID,							//����CPU ID��ACK
     OPEN_FLASH_PROTECTION,					//�_��FLASH���o
	   ACK_OPEN_FLASH_PROTECTION,			//�_��FLASH���o��ACK
		 CLOSE_FLASH_PROTECTION,				//�P�]FLASH���o
		 ACK_CLOSE_FLASH_PROTECTION,		//�P�]FLASH���o��ACK
	   READ_ALL_DATA,								 //�xȡ����׃���Y��(���o�Ƿ��_����cpu id ��̖��ֵ
		 ACK_READ_ALL_DATA,
		 WRITE_ALL_DATA,								//���������Y��
		 ACK_WRITE_ALL_DATA,							//���������Y�ϵ�ACK
		 SET_TEMP,
		 SET_TEMP_ON_OFF
		 //GO_TO_TEST_MODE                //�ྀ�K���M��yԇģʽ
};
#endif /*_usart_H*/

/*********************************END OF FILE**********************************/
