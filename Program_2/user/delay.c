#include "delay.h"

static u8  fac_us=0;//us delay
static u16 fac_ms=0;//ms delay

void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&=0xfffffffb;
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
 
}		

void delay_ms(u16 nms)
{	 		  	  
// 	u32 temp;		   
// 	SysTick->LOAD=(u32)nms*fac_ms;
// 	SysTick->VAL =0x00;           
// 	SysTick->CTRL=0x01 ;         
// 	do
// 	{
// 		temp=SysTick->CTRL;
// 	}
// 	while(temp&0x01&&!(temp&(1<<16)));  
// 	SysTick->CTRL=0x00;       
// 	SysTick->VAL =0X00;       	  
	Soft_delay_ms(nms);
}   

void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us;  		 
	SysTick->VAL=0x00;        
	SysTick->CTRL=0x01 ;       	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));   
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;       	 
}
/*********************软件延时*******************/
//软件延时函数，us级别
void Soft_delay_us(u16 time)
{    
   u32 i;  
   while(time--)
   {
      i=8;  //自己定义  调试时间：20141116
      while(i--){};
        __nop();
        __nop();
        __nop();
        __nop();
   }
}

//软件延时函数，ms级别
void Soft_delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=7950;  //自己定义  调试时间：20141116
      while(i--) ;    
   }
}