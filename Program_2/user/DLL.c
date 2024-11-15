#include "main.h"
#include "DLL.h"
#include "i2c.h"
#include "delay.h"
#include "stdio.h"


void DLL_Test(void)
{

	uint8_t reg;
	uint8_t val;
	uint8_t data[2];
	uint32_t i=0;
	
while(1){
	DEBUG("DLL Write OK %d\r\n",i);
	++i;
	// 	//Control PWM EN
	data[0] = 0xFF;
 	data[1] = 0x3F;
	IICwriteBytes(DLL_ADDR,0x04,sizeof(data),data);
	delay_ms(100);
	data[0] = 0xFF;
 	data[1] = 0x3F;
	IICwriteBytes(DLL_ADDR,0x04,sizeof(data),data);
	//
	
	//Control PWM VBO 000  11.6V
	data[0] = 0x00;
 	data[1] = 0x00;
	IICwriteBytes(DLL_ADDR,0x01,sizeof(data),data);
	delay_ms(10);
	data[0] = 0x00;
 	data[1] = 0x00;
	IICwriteBytes(DLL_ADDR,0x01,sizeof(data),data);
	// 	
	
	//
	delay_ms(1000);
  //Control PWM VBO 001  16V
	data[0] = 0x11;
 	data[1] = 0x01;
	IICwriteBytes(DLL_ADDR,0x01,sizeof(data),data);
	delay_ms(10);
	data[0] = 0x11;
 	data[1] = 0x01;
	IICwriteBytes(DLL_ADDR,0x01,sizeof(data),data);
	//
	
	delay_ms(1000);
	
 	//Control PWM VBO 011  25.2V
	data[0] = 0x33;
 	data[1] = 0x03;
	IICwriteBytes(DLL_ADDR,0x01,sizeof(data),data);
	delay_ms(10);
	data[0] = 0x33;
 	data[1] = 0x03;
	IICwriteBytes(DLL_ADDR,0x01,sizeof(data),data);
	//
	
	delay_ms(1000);
	}
}