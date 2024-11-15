#include "usart.h"

#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


//uart reicer flag
#define b_uart_head  0x80  //�յ�A5 �^ ���Iλ
#define b_rx_over    0x40  //�յ������Ď����I
// USART Receiver buffer
#define RX_BUFFER_SIZE 100 //���վ��n�^�ֹ���

void Decode_frame(unsigned char data);
volatile unsigned char rx_buffer[RX_BUFFER_SIZE]; //���Ք������n�^
volatile unsigned char rx_wr_index; //���n��ָ�
volatile unsigned char RC_Flag;  //���ՠ�B���I�ֹ�

volatile unsigned char usb_data[64]; //���Ք������n�^

//������ĽǶ�ֵ
float 	yaw,  //ƫ����
		pitch,//����
		roll, //�L�D
		alt,  //�߶�
		tempr,//�ض�
		press;//�≺
//ADCֵ
int16_t ax, ay, az;//���ٶ�Ӌ
int16_t gx, gy, gz;//���݃x
int16_t hx, hy, hz;//����Ӌ
//GPSλ����Ϣ
float GPS_Altitude , //�쾀�x��ƽ��ĸ߶ȣ�-9999.9��9999.9��
	  Latitude_GPS , //����	 ��λ���
	  Longitude_GPS , //����  ��λ���
	  Speed_GPS , //��������  ��λ  ��ÿ��
	  Course_GPS ; //���溽��000.0~359.9�ȣ����汱�酢������)
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


//�ڽ�����һ��IMU�ˑB����ᣬ�{���@���ӳ����ȡ���ˑB����
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
	yaw=(float)temp / 10.0f; //ƫ����
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	pitch=(float)temp / 10.0f;//����
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	roll=(float)temp / 10.0f;//�L�D

	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	alt=(float)temp / 10.0f;//�߶�
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	tempr=(float)temp / 10.0f;//�ض�
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	press=(float)temp * 10.0f;//�≺

}

//�ڽ���һ��ReportMotion ���{���@���ӳ����ȡ��ADC����
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
	ax=temp;//���ٶ�Ӌ X�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[4];
	temp <<= 8;
	temp |= rx_buffer[5];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	ay=temp;//���ٶ�Ӌ Y�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[6];
	temp <<= 8;
	temp |= rx_buffer[7];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	az=temp;//���ٶ�Ӌ Z�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[8];
	temp <<= 8;
	temp |= rx_buffer[9];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gx=temp;//���݃x X�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[10];
	temp <<= 8;
	temp |= rx_buffer[11];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gy=temp;//���݃x Y�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[12];
	temp <<= 8;
	temp |= rx_buffer[13];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	gz=temp;//���݃x Z�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[14];
	temp <<= 8;
	temp |= rx_buffer[15];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hx=temp;//����Ӌ X�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[16];
	temp <<= 8;
	temp |= rx_buffer[17];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hy=temp;//����Ӌ Y�S��ADCֵ
	
	temp = 0;
	temp = rx_buffer[18];
	temp <<= 8;
	temp |= rx_buffer[19];
	if(temp&0x8000){
	temp = 0-(temp&0x7fff);
	}else temp = (temp&0x7fff);
	hz=temp;//����Ӌ Z�S��ADCֵ
}


void USART2_IRQHandler(void)
{
	 unsigned char data;
 if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //�Ƿ��յ�����?
  {
  data=USART_ReceiveData(USART2); //�xȡ���յ����ֹ�
			
  Decode_frame(data);	//�M��⎬����
  /* Clear the USART2 Recive interrupt */
  USART_ClearITPendingBit(USART2, USART_IT_RXNE); //���Д����I.
  }
			
}


//--У򞮔ǰ���յ���һ�������Ƿ� �c��У��ֹ�һ��
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



//--�@���ӳ�����Ҫ���������� ���r�{��,�ԙz�� �����Ƿ������һ������
void UART2_CommandRoute(void)
{

 if(RC_Flag&b_rx_over){  //�ѽ�������һ��?
		RC_Flag&=~b_rx_over; //����I��
	 
	
		if(Sum_check()){ 
		//У�ͨ�^
			// printf("OK %x %x %x %x\r\n",rx_buffer[0],rx_buffer[1],rx_buffer[22],rx_buffer[23]);
		if(rx_buffer[1]==0xA3){ //UART2_ReportMotion �Ĕ���
		 //UART2_Get_Motion();	 //ȡ����
			
		
		} 
// 		if(rx_buffer[1]==0xA1){ //UART2_ReportIMU �Ĕ���
// 		 //UART2_Get_IMU();	//ȡ����
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
// 		if(rx_buffer[1]==0xA2){ //UART2_ReportMotion �Ĕ���
// 		 //UART2_Get_Motion();	 //ȡ����
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
		 
		}//У��Ƿ�ͨ�^?
	}
}

//�յ�һ���ֹ��{��һ�Ρ����յ����ֹ�����ݔ�롣
void Decode_frame(unsigned char data){

  if(data==0xa5) 
  { 
	RC_Flag|=b_uart_head; //������յ�A5 ��λ���^�ˌ�λ
    rx_buffer[rx_wr_index++]=data; //�����@���ֹ�.

  }
  else if(data==0x5a)
       { 
	   if(RC_Flag&b_uart_head) //�����һ���ֹ���A5 ���N�J�� �@���ǎ���ʼ�ֹ�
	     { rx_wr_index=0;  //���� ���n�^ָ�
		   RC_Flag&=~b_rx_over; //�@�����ń����_ʼ��
         }
         else //��һ���ֹ�����A5
				rx_buffer[rx_wr_index++]=data;
         RC_Flag&=~b_uart_head; //�厬�^���I
       }
	   else
	   { rx_buffer[rx_wr_index++]=data;
		 RC_Flag&=~b_uart_head;
		 if(rx_wr_index==rx_buffer[0]) //�Չ����ֹ���.
	     {  
			RC_Flag|=b_rx_over; //��λ ����������һ������
			UART2_CommandRoute(); //������ȡ������
          }
	   }

  if(rx_wr_index==RX_BUFFER_SIZE) //��ֹ���n�^���
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


