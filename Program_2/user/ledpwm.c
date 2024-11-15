#include "ledpwm.h"

uint16_t LED_PWM = 0;
static void timer4_PWM_Init(void);
void LEDPWMInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    uint16_t PrescalerValue = 0;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4,ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM4,DISABLE);
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3,ENABLE);
		RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM3,DISABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6 |GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
// GPIO_InitTypeDef GPIO_InitStructure;
//     
//     /* 设置TIM4CLK为72MHZ */
//     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 

//     /* GPIOB clock enable, Enable AFIO function */
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE); 
//     
//     /* PB6,7,8,9 -> timer4: Config to PWM output mode */
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            // 复用推挽输出
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     
//     GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
//     GPIO_Init(GPIOB, &GPIO_InitStructure);    
     TIM_DeInit(TIM4);

    PrescalerValue = (uint16_t) (SystemCoreClock / 8000000) - 1;
    
    TIM_TimeBaseStructure.TIM_Period = 719;//999;
    TIM_TimeBaseStructure.TIM_Prescaler =9;//PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//0;	
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 360;    //0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
   
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);
    TIM_OC2Init(TIM4,&TIM_OCInitStructure);
//    TIM_OC3Init(TIM4,&TIM_OCInitStructure);
//     TIM_OC4Init(TIM4,&TIM_OCInitStructure);
//     
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
// //     TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
// //     TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_Cmd(TIM4,ENABLE);
		
		TIM_CtrlPWMOutputs(TIM4,ENABLE);
		
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3 , ENABLE);
		
		  TIM_DeInit(TIM3);

    PrescalerValue = (uint16_t) (SystemCoreClock / 8000000) - 1;
    
    TIM_TimeBaseStructure.TIM_Period = 719;//999;
    TIM_TimeBaseStructure.TIM_Prescaler =9;//PrescalerValue;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//0;	
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);

    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 360;    //0
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
   
    TIM_OC1Init(TIM3,&TIM_OCInitStructure);
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);
   TIM_OC3Init(TIM3,&TIM_OCInitStructure);
    TIM_OC4Init(TIM3,&TIM_OCInitStructure);
//     
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_Cmd(TIM3,ENABLE);
		
		TIM_CtrlPWMOutputs(TIM3,ENABLE);
//timer4_PWM_Init();
}

#define PWM_FREQENCY  4000
static void timer4_PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    
    TIM_InternalClockConfig(TIM4);  
    
    /* Time base configuration */    
    TIM_TimeBaseStructure.TIM_Prescaler = 71;        // prescaler = 71, TIM_CLK = 72MHZ/(71+1) = 1MHZ.     
    TIM_TimeBaseStructure.TIM_Period = PWM_FREQENCY -1 ;         // 当定时器从0计数到999，即为1000次，为一个定时周期
                                                    // pwm F = 1MHZ/(3999+1) = 250HZ.  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;    //设置时钟分频系数：不分频(这里用不到)
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;       //配置为PWM模式1
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //当定时器计数值小于CCR1_Val时为高电平

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse =0;            //设置通道4的电平跳变值，输出另外一个占空比的PWM
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);                        //使能通道1
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;            //设置通道4的电平跳变值，输出另外一个占空比的PWM
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);                        //使能通道2
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    
    
    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;            //设置通道4的电平跳变值，输出另外一个占空比的PWM
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);                        //使能通道3
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;            //设置通道4的电平跳变值，输出另外一个占空比的PWM
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);                        //使能通道4
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM4, ENABLE);                                // 使能TIM3重载寄存器ARR

    /* TIM4 enable counter */
    TIM_Cmd(TIM4, ENABLE);                                         //使能定时器4  
}


void set_12V_relay_on(uint8_t ch){	
	switch (ch){
		case 1: _12V_CH1_ON; break;
		case 2: _12V_CH2_ON; break;
		case 3: _12V_CH3_ON; break;
		case 4: _12V_CH4_ON; break;
		case 5: _12V_CH5_ON; break;
		case 6: _12V_CH6_ON; break;
		case 7: _12V_CH7_ON; break;
		case 8: _12V_CH8_ON; break;
		default: break;
	}
}

void set_12V_relay_off(uint8_t ch){	
	switch (ch){
		case 1: _12V_CH1_OFF; break;
		case 2: _12V_CH2_OFF; break;
		case 3: _12V_CH3_OFF; break;
		case 4: _12V_CH4_OFF; break;
		case 5: _12V_CH5_OFF; break;
		case 6: _12V_CH6_OFF; break;
		case 7: _12V_CH7_OFF; break;
		case 8: _12V_CH8_OFF; break;
		default: break;
	}
}


void set_110V_relay_on(uint8_t ch){	
	switch (ch){
		case 1: _110V_CH1_ON; break;
		case 2: _110V_CH2_ON; break;
		case 3: _110V_CH3_ON; break;
		case 4: _110V_CH4_ON; break;
		default: break;
	}
}

void set_110V_relay_off(uint8_t ch){	
	switch (ch){
		case 1: _110V_CH1_OFF; break;
		case 2: _110V_CH2_OFF; break;
		case 3: _110V_CH3_OFF; break;
		case 4: _110V_CH4_OFF; break;
		default: break;
	}
}
void set_3V3_trigger_on(uint8_t ch){	
	switch (ch){
		case 1: _3V3V_CH5_ON; break;
		case 2: _3V3V_CH6_ON; break;
		case 3: _3V3V_CH7_ON; break;
		case 4: _3V3V_CH8_ON; break;
		default: break;
	}
}

void set_3V3_trigger_off(uint8_t ch){	
	switch (ch){
		case 1: _3V3V_CH5_OFF; break;
		case 2: _3V3V_CH6_OFF; break;
		case 3: _3V3V_CH7_OFF; break;
		case 4: _3V3V_CH8_OFF; break;
		default: break;
	}
}
void IOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 |GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
// 	
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
// 	GPIO_Init(GPIOC, &GPIO_InitStruct);
// 	
	
	RCC_LSEConfig(RCC_LSE_OFF);
	
// 	
// 	_12V_CH1_OFF;
// 	_12V_CH2_OFF;
// 	_12V_CH3_OFF;
// 	_12V_CH4_OFF;
// 	_12V_CH5_OFF;
// 	_12V_CH6_OFF;
// 	_12V_CH7_OFF;
// 	_12V_CH8_OFF;
// 	
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_12| GPIO_Pin_13;
// 	GPIO_Init(GPIOB, &GPIO_InitStruct);
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_7;
// 	GPIO_Init(GPIOA, &GPIO_InitStruct);
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
// 	GPIO_Init(GPIOC, &GPIO_InitStruct);
// 	
// 	_110V_CH1_OFF;
// 	_110V_CH2_OFF;
// 	_110V_CH3_OFF;
// 	_110V_CH4_OFF;
// 	_3V3V_CH5_OFF;
// 	_3V3V_CH6_OFF;
// 	_3V3V_CH7_OFF;
// 	_3V3V_CH8_OFF;
}

void LEDSetPWM(uint16_t LED_PWM)
{		
     if(LED_PWM>=LED_MAXPWM)	LED_PWM = LED_MAXPWM;
     if(LED_PWM<=0)	LED_PWM = 0;
		 TIM4->CCR1 = LED_PWM;

}

uint16_t LEDGetPWM(void)
{
	return TIM4->CCR1;
}
