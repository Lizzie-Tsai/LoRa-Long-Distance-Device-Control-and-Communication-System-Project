#include "usart.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


//uart reicer flag
#define b_uart_head  0x80  //收到A5 頭 標誌位
#define b_rx_over    0x40  //收到完整的幀標誌
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //接收緩衝區字節數

void Decode_frame(unsigned char data);
volatile unsigned char rx_buffer[RX_BUFFER_SIZE]; //接收數據緩衝區
volatile unsigned char rx_wr_index; //緩衝寫指針
volatile unsigned char RC_Flag;  //接收狀態標誌字節

volatile unsigned char usb_data[64]; //接收數據緩衝區

//解算後的角度值
float 	yaw,  //偏航角
		pitch,//俯仰
		roll, //滾轉
		alt,  //高度
		tempr,//溫度
		press;//氣壓
//ADC值
int16_t ax, ay, az;//加速度計
int16_t gx, gy, gz;//陀螺儀
int16_t hx, hy, hz;//磁力計
//GPS位置信息
float GPS_Altitude , //天線離海平面的高度，-9999.9到9999.9米
	  Latitude_GPS , //緯度	 單位為度
	  Longitude_GPS , //經度  單位為度
	  Speed_GPS , //地面速率  單位  米每秒
	  Course_GPS ; //地面航向（000.0~359.9度，以真北為參考基準)
unsigned char GPS_STA_Num ;



void USART_RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
}

void USART_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	//UART2
// 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
// 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOA, &GPIO_InitStruct);

// 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
// 	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//UART1
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStruct;
 NVIC_InitTypeDef NVIC_InitStruct;
	USART_RCC_Configuration();

	USART_GPIO_Configuration();
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART2, &USART_InitStruct);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);  
	USART_Cmd(USART2, ENABLE);

	
	USART_Init(USART1, &USART_InitStruct);     
	USART_Cmd(USART1, ENABLE);	

	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

extern uint8_t UART_buffer[30];
extern __IO uint8_t uart_data;
uint8_t uart_count=0;


//在接收完一幀IMU姿態報告後，調用這個子程序來取出姿態數據
void UART2_Get_IMU(void)
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	yaw=(float)temp / 10.0f; //偏航角
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	pitch=(float)temp / 10.0f;//俯仰
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	roll=(float)temp / 10.0f;//滾轉

	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	alt=(float)temp / 10.0f;//高度
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	tempr=(float)temp / 10.0f;//溫度
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	press=(float)temp * 10.0f;//氣壓

}

//在接收一幀ReportMotion 後調用這個子程序來取出ADC數據
void UART2_Get_Motion(void)
{
	int16_t temp;
	
	temp = 0;
	temp = rx_buffer[2];
	temp <<= 8;
	temp |= rx_buffer[3];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ax=temp;//加速度計 X軸的ADC值
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ay=temp;//加速度計 Y軸的ADC值
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	az=temp;//加速度計 Z軸的ADC值
	
	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gx=temp;//陀螺儀 X軸的ADC值
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gy=temp;//陀螺儀 Y軸的ADC值
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gz=temp;//陀螺儀 Z軸的ADC值
	
	temp = 0;
	temp = rx_buffer[14];
	temp <<= 8;
	temp |= rx_buffer[15];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hx=temp;//磁力計 X軸的ADC值
	
	temp = 0;
	temp = rx_buffer[16];
	temp <<= 8;
	temp |= rx_buffer[17];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hy=temp;//磁力計 Y軸的ADC值
	
	temp = 0;
	temp = rx_buffer[18];
	temp <<= 8;
	temp |= rx_buffer[19];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hz=temp;//磁力計 Z軸的ADC值
}


void USART2_IRQHandler(void)
{
	 unsigned char data;
 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //是否收到數據?
  {
  data=USART_ReceiveData(USART2); //讀取接收到的字節
			
  Decode_frame(data);	//進入解幀程序
  /* Clear the USART2 Recive interrupt */
  USART_ClearITPendingBit(USART2, USART_IT_RXNE); //清中斷標誌.
  }
			
}


//--校驗當前接收到的一幀數據是否 與幀校驗字節一致
unsigned char Sum_check(void)
{ 
  unsigned char i;
  unsigned int checksum=0; 
  for(i=0;i<rx_buffer[0]-2;i++)
   checksum+=rx_buffer[i];
  if((checksum%256)==rx_buffer[rx_buffer[0]-2])
   return(0x01); //Checksum successful
  else
   return(0x00); //Checksum error
}



//--這個子程序需要在主程序中 定時調用,以檢查 串口是否接收完一幀數據
void UART2_CommandRoute(void)
{

 if(RC_Flag&b_rx_over){  //已經接收完一幀?
		RC_Flag&=~b_rx_over; //清標誌先
	 
	
		if(Sum_check()){ 
		//校驗通過
			// printf("OK %x %x %x %x\r\n",rx_buffer[0],rx_buffer[1],rx_buffer[22],rx_buffer[23]);
		if(rx_buffer[1]==0xA3){ //UART2_ReportMotion 的數據
		 //UART2_Get_Motion();	 //取數據
			
		
		} 
// 		if(rx_buffer[1]==0xA1){ //UART2_ReportIMU 的數據
// 		 //UART2_Get_IMU();	//取數據
// 			usb_data[0]=0x1A;
// 			
// 			usb_data[2]=rx_buffer[2]; //Yaw
// 			usb_data[3]=rx_buffer[3];
// 			
// 			usb_data[4]=rx_buffer[4]; //Pitch
// 			usb_data[5]=rx_buffer[5];
// 			
// 			usb_data[6]=rx_buffer[6]; //Roll
// 			usb_data[7]=rx_buffer[7];
// 			
// 			usb_data[8]=rx_buffer[8]; //Height
// 			usb_data[9]=rx_buffer[9];
// 			
// 			usb_data[10]=rx_buffer[10]; //Temperature
// 			usb_data[11]=rx_buffer[11];
// 			
// 				//USB_SendString(rx_buffer);
// 		}
// 		if(rx_buffer[1]==0xA2){ //UART2_ReportMotion 的數據
// 		 //UART2_Get_Motion();	 //取數據
// 			
// 			usb_data[12]=rx_buffer[2]; //Accx
// 			usb_data[13]=rx_buffer[3];
// 			
// 			usb_data[14]=rx_buffer[4]; //Accy
// 			usb_data[15]=rx_buffer[5];
// 			
// 			usb_data[16]=rx_buffer[6]; //Accz
// 			usb_data[17]=rx_buffer[7];
// 			
// 			usb_data[18]=rx_buffer[8]; //Gx
// 			usb_data[19]=rx_buffer[9];
// 			
// 			usb_data[20]=rx_buffer[10]; //Gy
// 			usb_data[21]=rx_buffer[11];
// 			
// 			usb_data[22]=rx_buffer[12]; //Gz
// 			usb_data[23]=rx_buffer[13];
// 			USB_SendString(usb_data);
// 		} 
		 
		}//校驗是否通過?
	}
}

//收到一個字節調用一次。把收到的字節做為輸入。
void Decode_frame(unsigned char data){

  if(data==0xa5) 
  { 
	RC_Flag|=b_uart_head; //如果接收到A5 置位幀頭標專位
    rx_buffer[rx_wr_index++]=data; //保存這個字節.

  }
  else if(data==0x5a)
       { 
	   if(RC_Flag&b_uart_head) //如果上一個字節是A5 那麼認定 這個是幀起始字節
	     { rx_wr_index=0;  //重置 緩衝區指針
		   RC_Flag&=~b_rx_over; //這個幀才剛剛開始收
         }
         else //上一個字節不是A5
				rx_buffer[rx_wr_index++]=data;
         RC_Flag&=~b_uart_head; //清幀頭標誌
       }
	   else
	   { rx_buffer[rx_wr_index++]=data;
		 RC_Flag&=~b_uart_head;
		 if(rx_wr_index==rx_buffer[0]) //收夠了字節數.
	     {  
			RC_Flag|=b_rx_over; //置位 接收完整的一幀數據
			UART2_CommandRoute(); //立即提取數據。
          }
	   }

  if(rx_wr_index==RX_BUFFER_SIZE) //防止緩衝區溢出
  rx_wr_index--;
}


PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1,(u8)ch);

	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

	return ch;
}
/**
  * @}
  */

/*********************************END OF FILE**********************************/


