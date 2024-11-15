
#ifndef _ADC_H
#define _ADC_H
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stm32f10x.h>
void ADCInit(void);
void ad7685_GetConversion(unsigned short *dataDac);
#endif /*_ADC_H*/

/*********************************END OF FILE**********************************/
