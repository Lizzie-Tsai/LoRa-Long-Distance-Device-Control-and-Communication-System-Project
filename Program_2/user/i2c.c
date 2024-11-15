#include "main.h"
#include "i2c.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"
u32 ulTimeOut_Time;
void IIC_Init(void)
{			
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;
 	  I2C_InitTypeDef     i2c_Init;
    GPIO_InitTypeDef    gpio_Init;
	    RCC_ClocksTypeDef   rcc_clocks;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
//  
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//  
	//GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
//  
// 	I2C_DeInit(I2C1);
//  
// 	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
// 	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
// 	I2C_InitStructure.I2C_ClockSpeed = 50000;
// 	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
// 	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
// 	I2C_InitStructure.I2C_OwnAddress1 = 0;
// 	I2C_Init(I2C1, &I2C_InitStructure);
//  
// 	I2C_Cmd(I2C1, ENABLE);
//	GPIO_InitTypeDef GPIO_InitStructure;
 //	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);			     
//  
//  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;	
//   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
//   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//   
//   GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinRemapConfig(GPIO_Remap_I2C1 , ENABLE);

		gpio_Init.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9;                         
    gpio_Init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_Init.GPIO_Mode  = GPIO_Mode_AF_OD;
    GPIO_Init(GPIOB, &gpio_Init);
	
	 i2c_Init.I2C_Mode                = I2C_Mode_I2C;
    i2c_Init.I2C_DutyCycle           = I2C_DutyCycle_2;
    i2c_Init.I2C_OwnAddress1         = 0x0;
    i2c_Init.I2C_Ack                 = I2C_Ack_Enable;
    i2c_Init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    i2c_Init.I2C_ClockSpeed          = 200000;
		
		RCC_GetClocksFreq(&rcc_clocks);
    ulTimeOut_Time = (rcc_clocks.SYSCLK_Frequency /10 *5 /1000);

    I2C_Init(I2C1, &i2c_Init);
		I2C_Cmd(I2C1, ENABLE);     
	DEBUG("[I2C]Init OK\r\n");
}

void write_pcf8574(uint8_t addr, uint8_t data) {
	uint8_t pcf_data = data;
	uint8_t pcf_addr = addr;
 
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, pcf_addr, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING));
	I2C_SendData(I2C1, pcf_data);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

	return;
}
u8 I2C_WriteByte(u8 xChip, u8 xAddr, u16 xDat)
{
    u32 tmr;
    u8 errcnt;

    errcnt = 0;

    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);                                                    
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));              
    if(tmr ==0) errcnt++;

    I2C_Send7bitAddress(I2C1, xChip, I2C_Direction_Transmitter);                        
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
    if(tmr ==0) errcnt++;

    I2C_SendData(I2C1, xAddr);                                       
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));         
    if(tmr ==0) errcnt++;

    I2C_SendData(I2C1, xDat>>8);                                             
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));         
    if(tmr ==0) errcnt++;

    I2C_SendData(I2C1, xDat);                                                           
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));         
    if(tmr ==0) errcnt++; 
    
    I2C_GenerateSTOP(I2C1, ENABLE);                                                     
    return(errcnt); 
}

u8 I2C_ReadByte(u8 xChip, u8 xAddr)
{
    u8 dat; 
    u8 errcnt;
    u32 tmr;

    errcnt = 0; 

    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);                                                    
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));             
    if(tmr ==0) errcnt++;

    I2C_Send7bitAddress(I2C1, xChip, I2C_Direction_Transmitter);                       
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
    if(tmr ==0) errcnt++;

//     I2C_SendData(I2C1, xAddr);                                      
//     tmr = ulTimeOut_Time;
//     while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));         
//     if(tmr ==0) errcnt++;

    I2C_SendData(I2C1, xAddr);                                             
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));       
    if(tmr ==0) errcnt++;

    I2C_GenerateSTART(I2C1, ENABLE);                                                   
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));              
    if(tmr ==0) errcnt++;

    I2C_Send7bitAddress(I2C1, xChip, I2C_Direction_Receiver);                           
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));   
    if(tmr ==0) errcnt++;

    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)));            
    if(tmr ==0) errcnt++;
   
    dat = I2C_ReceiveData(I2C1);                                                      
		printf("%x\r\n",dat);
		
    I2C_GenerateSTOP(I2C1, ENABLE);                                                     
    return(dat);
}



u16 I2C_ReadBytes(u8 xChip, u8 xAddr)
{
    u8 dat,dat2; 
    u8 errcnt;
    u32 tmr;

    errcnt = 0; 

    while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2C1, ENABLE);                                                    
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));             
    if(tmr ==0) errcnt++;

    I2C_Send7bitAddress(I2C1, xChip, I2C_Direction_Transmitter);                       
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
    if(tmr ==0) errcnt++;

//     I2C_SendData(I2C1, xAddr);                                      
//     tmr = ulTimeOut_Time;
//     while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));         
//     if(tmr ==0) errcnt++;

    I2C_SendData(I2C1, xAddr);                                             
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));       
    if(tmr ==0) errcnt++;

    I2C_GenerateSTART(I2C1, ENABLE);                                                   
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));              
    if(tmr ==0) errcnt++;

    I2C_Send7bitAddress(I2C1, xChip, I2C_Direction_Receiver);                           
    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));   
    if(tmr ==0) errcnt++;

    tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)));            
    if(tmr ==0) errcnt++;
   
    dat = I2C_ReceiveData(I2C1);                                                      
		//printf("%x\r\n",dat);
		  tmr = ulTimeOut_Time;
    while((tmr--)&&(!I2C_CheckEvent(I2C1,I2C_EVENT_MASTER_BYTE_RECEIVED)));            
    if(tmr ==0) errcnt++;
		 dat2 = I2C_ReceiveData(I2C1);     
		 //printf("%x\r\n",dat);
    I2C_GenerateSTOP(I2C1, ENABLE);                                                     
    return(dat<<8|dat2);
}




void I2C_WriteBytes(u8 xChip, u16 xAddr, u16 xLen, u8 *xpBuf)
{
 u8 *pbuf;
 u8 err;
 u8 retry;
 u16 addr;
 u16 len;

 pbuf = xpBuf;
 addr = xAddr;
 len  = xLen;

 retry = 5;              

 while(len)
 {
  err = I2C_WriteByte(xChip, addr, *pbuf);

  if(err)
  {
   if(--retry == 0 )
   {
    retry = 5;         

    pbuf++;
    addr++;
    len--;
   }
  }
  else
  {
   pbuf++;
   addr++;
   len--;
  }
 }
}

void IIC_Start(void)
{
	SDA_OUT();    
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(20);
 	IIC_SDA=0;
	delay_us(20);
	IIC_SCL=0;
}
void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;
 	delay_us(20);
	IIC_SCL=1; 
	IIC_SDA=1;
	delay_us(20);							   	
}

u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();     
	IIC_SDA=1;delay_us(5);	   
	IIC_SCL=1;delay_us(5);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>100)
		{
			IIC_Stop();
			return 1;
		}
	  delay_us(5);
	}
	IIC_SCL=0;
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(10);
	IIC_SCL=1;
	delay_us(10);
	IIC_SCL=0;
}

void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(10);
	IIC_SCL=1;
	delay_us(10);
	IIC_SCL=0;
}					 				     

void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {              
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(10);   
		IIC_SCL=1;
		delay_us(10); 
		IIC_SCL=0;	
		delay_us(10);
    }	 
} 	 

u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(2); 
    }					 
    if (ack)
        IIC_Ack(); 
    else
        IIC_NAck(); 
    return receive;
}

unsigned char I2C_ReadOneByte(unsigned char I2C_Addr,unsigned char addr)
{
	unsigned char res=0;
	
	IIC_Start();
	IIC_Send_Byte(I2C_Addr);	   
	res++;
	IIC_Wait_Ack();
	IIC_Send_Byte(addr); res++;  
	IIC_Wait_Ack();	  
	//IIC_Stop();
	IIC_Start();
	IIC_Send_Byte(I2C_Addr+1); res++;       	   
	IIC_Wait_Ack();
	res=IIC_Read_Byte(0);	   
    IIC_Stop();
	return res;
}

u8 IICreadBytes(u8 dev, u8 reg, u8 length, u8 *data){
    u8 count = 0;
	u8 temp;
	IIC_Start();
	IIC_Send_Byte(dev);	   
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);   
    IIC_Wait_Ack();	  
	IIC_Start();
	IIC_Send_Byte(dev+1);  
	IIC_Wait_Ack();
	
    for(count=0;count<length;count++){
		 
		 if(count!=(length-1))
		 	temp = IIC_Read_Byte(1); 
		 	else  
			temp = IIC_Read_Byte(0);	

		data[count] = temp;
	}
    IIC_Stop();
    return count;
}

u8 IICwriteBytes(u8 dev, u8 reg, u8 length, u8* data){
  
 	u8 count = 0;
	IIC_Start();
	IIC_Send_Byte(dev);	   
	IIC_Wait_Ack();
	IIC_Send_Byte(reg);   
  IIC_Wait_Ack();	  
	for(count=0;count<length;count++){
		IIC_Send_Byte(data[count]); 
		IIC_Wait_Ack(); 
	 }
	IIC_Stop();
    return 1; 
}

u8 IICreadByte(u8 dev, u8 reg, u8 *data){
	*data=I2C_ReadOneByte(dev, reg);
    return 1;
}

unsigned char IICwriteByte(unsigned char dev, unsigned char reg, unsigned char data){
    return IICwriteBytes(dev, reg, 1, &data);
}

u8 IICwriteBits(u8 dev,u8 reg,u8 bitStart,u8 length,u8 data)
{

    u8 b;
    if (IICreadByte(dev, reg, &b) != 0) {
        u8 mask = (0xFF << (bitStart + 1)) | 0xFF >> ((8 - bitStart) + length - 1);
        data <<= (8 - length);
        data >>= (7 - bitStart);
        b &= mask;
        b |= data;
        return IICwriteByte(dev, reg, b);
    } else {
        return 0;
    }
}

u8 IICwriteBit(u8 dev, u8 reg, u8 bitNum, u8 data){
    u8 b;
    
    IICreadByte(dev, reg, &b);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    
    return IICwriteByte(dev, reg, b);
}
