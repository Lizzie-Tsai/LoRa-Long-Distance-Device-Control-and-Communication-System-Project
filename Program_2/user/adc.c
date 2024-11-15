#include "adc.h"
#include "delay.h";


#define Set_AD_CNV()       	GPIO_SetBits(GPIOB,GPIO_Pin_2);

#define Clr_AD_CNV()        GPIO_ResetBits(GPIOB,GPIO_Pin_2); 
#define Read_AD_SDO()       GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)
#define Set_AD_SCK()        GPIOA->BSRR=GPIO_Pin_5
#define Clr_AD_SCK()        GPIOA->BRR=GPIO_Pin_5

extern __IO float voltage;
extern __IO uint16_t raw;
void ad7685_GetConversion(unsigned short *dataDac){

// 	Clr_AD_CNV();
// 	Set_AD_CNV();
// 	delay_us(2);
	Clr_AD_CNV();

 	while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, 0x06); 
  while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	SPI_I2S_ReceiveData(SPI1);
		while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPI1, 0x0); 
  while (SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET);
	//raw=SPI_I2S_ReceiveData(SPI1);
// 	 *dataDac=SPI_I2S_ReceiveData(SPI1);
	 Set_AD_CNV();
  //printf("1:%x\r\n",SPI_I2S_ReceiveData(SPI1)); 
	 //voltage = 4.5 *raw / (1ul << 16);
	printf("ww %x\r\n",SPI_I2S_ReceiveData(SPI1));
	//Vout=-Vin(0.2262443438914027)+2.256289592760181
	//Vin(0.2262443438914027)=2.256289592760181-Vout
	//Vin=(2.256289592760181-Vout)/0.2262443438914027
	
	
	 //printf("%f %f %x\r\n",voltage,(2.256289592760181-voltage)/0.2262443438914027,raw);
 	 //voltage1=voltage*100.0f;
// printf("%f\r\n",voltage1);
	
	//delay_ms(10);

}
void ADCInit(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		ADC_InitTypeDef ADC_InitStructure;
   
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); //ADCCLK = PCLK22/6 = 72/6=12MHz
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Enable ADC1 Clock

    /* ADC1 configuration */
    ADC_DeInit(ADC1); //Power-on default
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //Independent conversion mode (single)
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; //Convert single channel only
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; //Convert 1 time
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //No external triggering
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //Right 12-bit data alignment
    ADC_InitStructure.ADC_NbrOfChannel = 1; //single channel conversion
    ADC_Init(ADC1, &ADC_InitStructure);
    ADC_Cmd(ADC1, ENABLE); //Enable ADC1
    ADC_ResetCalibration(ADC1); //Enable ADC1 reset calibration register
    while(ADC_GetResetCalibrationStatus(ADC1)); //check the end of ADC1 reset calibration register  
    ADC_StartCalibration(ADC1); //Start ADC1 calibration
    while(ADC_GetCalibrationStatus(ADC1)); //Check the end of ADC1 calibration
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_239Cycles5); //Select 1.5 cycles conversion for channel 16

}
/*********************************END OF FILE**********************************/

