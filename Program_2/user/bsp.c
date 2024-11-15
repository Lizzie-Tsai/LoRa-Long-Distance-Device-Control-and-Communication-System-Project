#include "bsp.h"
#include "main.h"

extern __IO uint32_t TypeAddress;
extern uint8_t MachType;


void Timer1_Init(u16 arr,u16 psc)  
{  
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  
  NVIC_InitTypeDef NVIC_InitStructure;  
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能  
  
  TIM_TimeBaseStructure.TIM_Period = arr-1; //设置自动重装载寄存器周期值  
  TIM_TimeBaseStructure.TIM_Prescaler =(psc-1);//设置预分频值  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV2; //设置时钟分割  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式  
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;//重复计数设置  
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //参数初始化  
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位  
  
  TIM_ITConfig(      //使能或者失能指定的TIM中断  
    TIM1,            //TIM1  
    TIM_IT_Update  | //TIM 更新中断源  
    TIM_IT_Trigger,  //TIM 触发中断源   
    ENABLE           //使能  
    );  
      
  //设置优先级  
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;//先占优先级0级  
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;       //从优先级0级  
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
  NVIC_Init(&NVIC_InitStructure);   
  
  TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设  
}  
void RCC_Configuration(void)

{
  /* PCLK2 = HCLK/2 */
  //RCC_PCLK2Config(RCC_HCLK_Div2);
  /* Enable peripheral clocks --------------------------------------------------*/
  /* GPIOA, GPIOB and SPI1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO|
                         RCC_APB2Periph_SPI1, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE); 
	//For USB Pull UP Pin
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
	DEBUG("GPIO %d\r\n",MachType);
	if(MachType==MASTER){
		DEBUG("MASTER GPIO\r\n");
		//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE); 
	//LED Status
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	delay_ms(200);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_SetBits(GPIOA,GPIO_Pin_5);
	}else{
		DEBUG("Slave GPIO\r\n");
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
		//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_15;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		GPIO_ResetBits(GPIOA,GPIO_Pin_13);
		GPIO_ResetBits(OUTPORT,OUT0);
		GPIO_ResetBits(OUTPORT,OUT1);
		GPIO_ResetBits(OUTPORT,OUT2);
// 		delay_ms(200);
// 		GPIO_SetBits(GPIOA,GPIO_Pin_13);

		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 |GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	}


}

void LEDToggle()
{
	GPIOA->ODR ^= GPIO_Pin_2;
}

void SPI_Configuration(uint8_t type)
{
	SPI_InitTypeDef  SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	if(type==MASTER){
	DEBUG("Master SPI\r\n");
		
  /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
  /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);


  /* Confugure MISO pin as Input Floating  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	/* CNV  */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE);
	}else{
		DEBUG("Slave SPI INIT\r\n");
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1, ENABLE); 

				 /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
			/* Confugure SCK and MOSI pins as Alternate Function Push Pull */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_7 ;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_Init(GPIOA, &GPIO_InitStructure);


			/* Confugure MISO pin as Input Floating  */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			

			/* CNV  */
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
//				GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);

	}
	/* SPI1 configuration ------------------------------------------------------*/

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
  SPI_Init(SPI1, &SPI_InitStructure); 

  /* Enable SPI1 */
  SPI_Cmd(SPI1, ENABLE);
}

void input_init(void)
{
	//結構宣告
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;

//設定PA0的GPIO

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10;
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU; //內部拉高
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

GPIO_Init(GPIOB, &GPIO_InitStructure);

//把EXTI0連到PB0 PB1 PB2 PB10

GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource2);
GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);

//設定EXTI0

EXTI_InitStructure.EXTI_Line = EXTI_Line0 ;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);
EXTI_InitStructure.EXTI_Line = EXTI_Line1 ;
EXTI_Init(&EXTI_InitStructure);
EXTI_InitStructure.EXTI_Line = EXTI_Line2 ;
EXTI_Init(&EXTI_InitStructure);
EXTI_InitStructure.EXTI_Line = EXTI_Line10 ;
EXTI_Init(&EXTI_InitStructure);
//設定NVIC

NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
NVIC_Init(&NVIC_InitStructure);
NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
NVIC_Init(&NVIC_InitStructure);
NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
NVIC_Init(&NVIC_InitStructure);

}
void bsp_init(void)
{
	RCC_Configuration();
	Set_System();
 //	delay_init(72);		
 	USART_Configuration();
	MachType=*(uint32_t*)TypeAddress;

	DEBUG("[USB Control Board V0.1]\r\n");
	GPIO_Configuration();
	//input_init();
if(MachType==SLAVE){
	//IIC_Init();
//	ADCInit();

// 	write_pcf8574(0x40,0x00);
// 	write_pcf8574(0x42,0x00);
// 	write_pcf8574(0x44,0x00);
// 	write_pcf8574(0x48,0x00);
//	IOInit();
	DEBUG("Motor\r\n");
	LEDPWMInit();
}else{
  //delay_ms(500);  //36000 1 sec
	Timer1_Init(2000,3600*1);
}
// 	ADCInit();
// 	LEDSetPWM(0);	
//	SMBus_init();
	
  USB_Interrupts_Config();
  Set_USBClock();
  USB_Init();

//	delay_ms(500);
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
	DEBUG("[USB On]\r\n");
	MachType=*(uint32_t*)TypeAddress;
	DEBUG("[Tye Addr]%x\r\n",MachType);
  //SPI_Configuration();

}

/*********************************END OF FILE**********************************/

