
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes */
#include "main.h"
#include "usart.h"
#include "spi.h"
#include "stm32h7xx_hal.h"

#include "lcd.h"
#include "i2c.h"
#include "key.h"
//SX1278
#include "platform.h"
#include "radio.h"
#include "sx1276-LoRaMisc.h"

#define MESSAGE    "Lora Project Demo" 
#define MESSAGE1   "Lora Project" 
#define MESSAGE2   " Testing on  " 
#define MESSAGE3   "   01" 

/*LM75A*/
uint16_t tempRaw;
uint16_t thystRaw;
uint16_t tosRaw;

GPIO_TypeDef* GPIO_PORT[LEDn] = {LED0_GPIO_PORT, LED1_GPIO_PORT,LED2_GPIO_PORT,LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED0_PIN, LED1_PIN,LED2_PIN,LED3_PIN};

uint8_t MachType=0;
tRadioDriver *Radio = NULL;
uint8_t PingMsg[] = "PING";
#define BUFFER_SIZE     20     
static uint16_t BufferSize = BUFFER_SIZE;			// RF buffer size
uint8_t  Buffer[BUFFER_SIZE];				// RF buffer
void OnSlave( void );

void LCDBanner(void);
uint8_t readtemp();
void LEDOff(Led_TypeDef Led);
void LEDOn(Led_TypeDef Led);
void LEDToggle(Led_TypeDef Led);

void MPU_Config(void);
void SystemClock_Config(void);
static void MX_GPIO_Init(void);


/**
  * @brief  The application entry point.
  *
  * @retval None
  */
	
int main(void)
{
	uint8_t i,txpwr,bw,sf,ec;
  uint32_t freq,rxtimeout,txtimeout;
	uint8_t buf[128];

  /* MCU Configuration*/
  MPU_Config();
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
  /* Configure the system clock */
  SystemClock_Config();
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
	MX_USART1_UART_Init();
	MX_SPI1_SPI_Init();
  I2C_EE_Init();
	EXTI_Key_Config(); 
	LCD_Initializtion();
	LCD_Clear(Blue2);
	LCDBanner();
		
	printf("\n\r %s", MESSAGE1);
  printf(" %s", MESSAGE2);
  printf(" %s\r\n", MESSAGE3);

	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);
	HAL_Delay(100);
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_3);

		
	MachType=SLAVE;
  Radio = RadioDriverInit(); 
  Radio->Init();
	

	SX1276LoRaSetRFFrequency(446000000);
  SX1276LoRaSetSignalBandwidth(8);
  SX1276LoRaSetSpreadingFactor(7);
  SX1276LoRaSetRxPacketTimeout(1000);
  SX1276LoRaSetTxPacketTimeout(1000);

	SX1276LoRaSetRxSingleOn(false);
	
	freq=SX1276LoRaGetRFFrequency();
	txpwr=SX1276LoRaGetRFPower();
	bw=SX1276LoRaGetSignalBandwidth();
	sf=SX1276LoRaGetSpreadingFactor();
	ec=SX1276LoRaGetErrorCoding();
	rxtimeout=SX1276LoRaGetRxPacketTimeout();
	txtimeout=SX1276LoRaGetTxPacketTimeout();
	
	sprintf(buf,"Freq:%d",freq);
	printf("%s\r\n",buf);
	GUI_Text(35,2*16+64,buf,Red,Blue2);
	sprintf(buf,"Txpwr:%d",txpwr);
	printf("%s\r\n",buf);
	GUI_Text(35,3*16+64,buf,Red,Blue2);
	sprintf(buf,"BW:%d",bw);
	printf("%s\r\n",buf);
	GUI_Text(35,4*16+64,buf,Red,Blue2);
	sprintf(buf,"SF:%d",sf);
	printf("%s\r\n",buf);
	GUI_Text(35,5*16+64,buf,Red,Blue2);
	sprintf(buf,"ec:%d",ec);
	printf("%s\r\n",buf);
	GUI_Text(35,6*16+64,buf,Red,Blue2);
	sprintf(buf,"rxtimeout:%d",rxtimeout);
	printf("%s\r\n",buf);
	GUI_Text(35,7*16+64,buf,Red,Blue2);
	sprintf(buf,"txtimeout:%d",txtimeout);
	printf("%s\r\n",buf);
	GUI_Text(35,8*16+64,buf,Red,Blue2);
	
	Radio->StartRx();

	readtemp();
	printf("LM75A temp: %2.3f\r\n",tempRaw*0.125);
	HAL_Delay(1000);
			
	while(1){
		OnSlave();
	}
}
/**
  * @brief LoRa Tx/Rx Tasks
  * @retval None
  */
void OnSlave( void )
{
	uint8_t i;
	switch( Radio->Process( ) )
	{
	case RF_RX_DONE:
		Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
		/** Message Recieved 
			*     index: [  0,   1,   2,   3,             4,       5,                12,    13,    14,          15,...20]
			*   content: ['P', 'I', 'N', 'G',    LED ON/OFF, LED num,..., Buzzer ON/OFF, LCD x, LCD y, LCD content,.....]
			*/
		if( BufferSize > 0 )
		{
			/* compare the recieved string */
			if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
			{
				printf("%d\r\n",BufferSize);
				/* Toggle the LED to show that the received frame is a PING */
				LEDToggle(LED1);
				printf("Get PING\r\n");
				/* LED:  Turn ON or OFF the specified LED depends on Buffer[4] and Buffer[5] */
				if(Buffer[4]==0xf0){
					LEDOn(Buffer[5]);
					printf("LED On %d\r\n",Buffer[5]);
				}else if(Buffer[4]==0xff){
					LEDOff(Buffer[5]);
					printf("LED Off %d\r\n",Buffer[5]);
				}
				/* BUZZER:  Turn ON or OFF the buzzer depends on Buffer[12] */
				if(Buffer[12]==0xf0){
					BEEP_ON();	
					printf("Beep on\r\n");
				}else{
					BEEP_OFF();	
					printf("Beep off\r\n");
				}
				/* LCD:  Show the text on LCD depends on Buffer[13], Buffer[13] and Buffer[15] */
				if(Buffer[13]!=0){
					printf("Write LCD\r\n");
					LCD_Clear(Blue2);
					GUI_Text(Buffer[13],Buffer[14],Buffer+15,Red,Blue2);
				}
				/** Send a PONG string as reply
				  * Reply Message index: [  0,   1,   2,   3, 4, 5,     6,     7,    8,    9,   10,   11, ..20]
				  *             content: ['P', 'O', 'N', 'G', X, X, TempL, TempH, Key0, Key1, Key2, Key3, ....]
					*/
				memset(Buffer,0x0,20);
				Buffer[0] = 'P';
				Buffer[1] = 'O';
				Buffer[2] = 'N';
				Buffer[3] = 'G';
				/* TEMP SENSOR:  Include temperature in the reply message*/
				readtemp();
				Buffer[6]=(tempRaw>>8)&0xff;
				Buffer[7]=(tempRaw)&0xff;
				printf("LM75A temp: %2.3f\r\n",tempRaw*0.125);
				/* KEY:  If a key is pressed, indicate through Buffer[8]-Buffer[11] in the reply message */
				if(STM_EVAL_PBGetState(KEY1)!=RESET){	printf("KEY0 pressed\r\n");Buffer[8]=1;}else{Buffer[8]=0x0;}
				if(STM_EVAL_PBGetState(KEY2)!=RESET){	printf("KEY1 pressed\r\n");Buffer[9]=1;}else{Buffer[9]=0x0;}
				if(STM_EVAL_PBGetState(KEY3)!=RESET){	printf("KEY2 pressed\r\n");Buffer[10]=1;}else{Buffer[10]=0x0;}
				if(STM_EVAL_PBGetState(KEY4)!=RESET){	printf("KEY3 pressed\r\n");Buffer[11]=1;}else{Buffer[11]=0x0;}

				Radio->SetTxPacket( Buffer, BufferSize );      //RFLR_STATE_TX_INIT
			}
		}
		break;
	case RF_TX_DONE:
		/* Toggle the LED to show that PONG is sent */
		LEDToggle(LED0);
		printf("Sent PONG\r\n");
		Radio->StartRx( );   //RFLR_STATE_RX_INIT
		break;
	default:
		break;
	}
}
/**
  * @brief Show Start Message on LCD
  * @retval None
  */
void LCDBanner(void)
{
	char data[50];
	uint32_t Dev_Serial0,Dev_Serial1,Dev_Serial2;
	uint32_t Dev_FlashSize;
	uint32_t Dev_Signature;
	Dev_Serial0 = *( __IO uint32_t*)(0x1FF1E800);
	Dev_Serial1 = *( __IO uint32_t*)(0x1FF1E804);
	Dev_Serial2 = *( __IO uint32_t*)(0x1FF1E808);
	Dev_FlashSize = *( __IO uint16_t*)(0x1FF1E880);
	
	printf("\r\n%s\r\n", MESSAGE);
	printf("Device Unique ID:0x%08x 0x%08x 0x%08x\r\n",Dev_Serial0,Dev_Serial1,Dev_Serial2);
	printf("Flash Size:%uKB\r\n",Dev_FlashSize);
	LCD_Clear(Blue2);
	GUI_Text(60,0,MESSAGE,White,Blue2);
	sprintf(data,"SN:0x%08x 0x%08x 0x%08x",Dev_Serial0,Dev_Serial1,Dev_Serial2);
	GUI_Text(35,16,data,White,Blue2);	
	sprintf(data,"Flash:%uKB ",Dev_FlashSize);
	GUI_Text(35,32,data,White,Blue2);	
	GUI_Text(35,48,MESSAGE2,White,Blue2);	
}
/**
  * @brief Read Temperature
  * @retval trivial
  */
uint8_t readtemp(){
	uint8_t tempData[2] = {0};
	I2C_Read(LM75A_ADDR,LM75A_REG_READ_TEMP,tempData,2);
	tempRaw = tempData[1]|(tempData[0] << 8 );
	tempRaw = tempRaw>>5;
	
	
  if ((tempData[0]& 0x80)==1)
	{
		tempRaw = -tempRaw;
		printf("%x %x %d %f\r\n",tempData[0],tempData[1],tempRaw,-tempRaw*0.125);
	}
	return 0;
}
/**
  * @brief LED Control
  * @retval None
  */
void LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRL = GPIO_PIN[Led];	
}

void LEDOn(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRH = GPIO_PIN[Led];		
}

void LEDToggle(Led_TypeDef Led)
{		
	GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];		
}
/**
  * @brief MPU Configuration
  * @retval None
  */
void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;
  
  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU attributes as WT for SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x20010000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Supply configuration update enable 
	*/
  MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);

	/**Configure the main internal regulator output voltage 
	*/
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) 
  {
    
  }
	/**Initializes the CPU, AHB and APB busses clocks 
	*/
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	/* Initializes the CPU, AHB and APB busses clocks */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

	/* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(SystemCoreClock/1000);

	/* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_R_Pin */
  GPIO_InitStruct.Pin = LED_R_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_R_GPIO_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_4;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	
		
	GPIO_InitStruct.Pin = GPIO_PIN_3 |GPIO_PIN_0;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void Soft_delay_ms(uint16_t time)
{  
  HAL_Delay(time);
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
