
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
		 CONNECT=66,										//連線
     ACK_CONNECT,										//連線的ACK
     DISCONNECT,        						//離線
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
	
     WRITE_SN,											//寫入序號
     ACK_WRITE_SN,									//寫入序號的ACK     
     WRITE_CPU_ID,									//寫入CPU ID
     ACK_WRITE_CPU_ID,							//寫入CPU ID的ACK
     OPEN_FLASH_PROTECTION,					//開啟FLASH保護
	   ACK_OPEN_FLASH_PROTECTION,			//開啟FLASH保護的ACK
		 CLOSE_FLASH_PROTECTION,				//關閉FLASH保護
		 ACK_CLOSE_FLASH_PROTECTION,		//關閉FLASH保護的ACK
	   READ_ALL_DATA,								 //讀取所有變動資料(保護是否開啟、cpu id 序號的值
		 ACK_READ_ALL_DATA,
		 WRITE_ALL_DATA,								//寫入所有資料
		 ACK_WRITE_ALL_DATA,							//寫入所有資料的ACK
		 SET_TEMP,
		 SET_TEMP_ON_OFF
		 //GO_TO_TEST_MODE                //斷線並且進入測試模式
};
#endif /*_usart_H*/

/*********************************END OF FILE**********************************/
