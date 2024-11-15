/*
	Howard.lin  howard.lin@cyess.com
*/
#include "main.h"
#include "bsp.h"
//SX1278
#include "platform.h"
#include "radio.h"
#include "sx1276-LoRaMisc.h"

#define  UPDATE_CODE  0xAE86
__IO uint32_t UpdateAddress=0x0800FFE0;
const uint32_t FlashBase=0x0800F800;
__IO uint32_t TypeAddress			=FlashBase;


extern  unsigned char usb_data[64];





static uint8_t EnableMaster = false; 
tRadioDriver *Radio = NULL;
uint8_t MY_TEST_Msg[] = "LoRa_SX1278_TEST";

uint8_t PingMsg[] = "PING";
uint8_t PongMsg[] = "PONG";
#define BUFFER_SIZE     30                          // Define the payload size here

static uint16_t BufferSize = BUFFER_SIZE;			// RF buffer size
static uint8_t  Buffer[BUFFER_SIZE];				// RF buffer




#define MMIO8(addr)  (*(volatile uint8_t *)(addr))
#define MMIO16(addr)  (*(volatile uint16_t *)(addr))
#define MMIO32(addr)  (*(volatile uint32_t *)(addr))
struct loraSet{
		char* Setting;
		uint8_t length;
		uint32_t addr;
}typedef loraSet;
#define Settinglength 11
#define TotalSettinglength 26
const struct loraSet LoraSet[]={
	{"TypeAddress",4,FlashBase},
	{"RFFrequency",4,FlashBase+4},
	{"TXPower",2,FlashBase+8},
	{"SignalBw",2,FlashBase+10},
	{"SpreadingFactor",2,FlashBase+12},
	{"ErrorCoding",2,FlashBase+14},
	{"TxPacketTimeout",2,FlashBase+16},
	{"RxPacketTimeout",2,FlashBase+18},
	{"PINPONGPeriod",2,FlashBase+20},
	{"MODE",2,FlashBase+22},
	{"ID",2,FlashBase+24},
};


void read_lora_setting_from_Flash(uint8_t* data)
{
	uint8_t i=0,j=0;
	for(i=0;i<Settinglength;i++){
		DEBUG("[%d] %s:%d\r\n",i,LoraSet[i].Setting,LoraSet[i].length==2?MMIO16(LoraSet[i].addr):MMIO32(LoraSet[i].addr));
		for(j=0;j<LoraSet[i].length;j++){
			*data=MMIO8(LoraSet[i].addr+j);
			data++;
		}
	}
	
}

void write_lora_setting_to_Flash(uint8_t* data)
{
	FLASH_Status FLASHStatus;
	uint8_t i=0,j=0;
	uint32_t tmp32;
	uint16_t tmp16;

	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
	FLASHStatus = FLASH_ErasePage(FlashBase); 
	for(i=0;i<Settinglength;i++){
		
			if(LoraSet[i].length==2){
				tmp16 =data[j]<<8|data[j+1];
				//DEBUG("16[%d] %d\r\n",i,tmp16);
				FLASHStatus = FLASH_ProgramHalfWord(LoraSet[i].addr, tmp16);
				j+=2;
			}else if(LoraSet[i].length==4){
				tmp32=data[j]<<24|data[j+1]<<16|data[j+2]<<8|data[j+3];
				//DEBUG("32[%d] %d\r\n",i,tmp32);
				FLASHStatus = FLASH_ProgramWord(LoraSet[i].addr, tmp32);
				j+=4;
			}
				//delay_ms(100);
		while(FLASHStatus != FLASH_COMPLETE){DEBUG("Wait\r\n");};
		
	//	DEBUG("[%d] %s:%x\r\n",i,LoraSet[i].Setting,LoraSet[i].length==2?MMIO16(LoraSet[i].addr):MMIO32(LoraSet[i].addr));
	}
	FLASH_Lock();
	
	
}

uint8_t MachType=0;
uint16_t ID=0;
void set_lora_para()
{
	//RFFrequency
	SX1276LoRaSetRFFrequency(MMIO32(LoraSet[1].addr));
	//TXPower
	SX1276LoRaSetRFPower(MMIO8(LoraSet[2].addr));
	//SignalBw
	SX1276LoRaSetSignalBandwidth(MMIO8(LoraSet[3].addr));
	//SpreadingFactor
	SX1276LoRaSetSpreadingFactor(MMIO8(LoraSet[4].addr));
	//ErrorCoding
	SX1276LoRaSetErrorCoding(MMIO8(LoraSet[5].addr));
	//TxPacketTimeout
	SX1276LoRaSetTxPacketTimeout(MMIO16(LoraSet[6].addr));
	//RxPacketTimeout
	//SX1276LoRaSetRxPacketTimeout(MMIO16(LoraSet[7].addr));
	SX1276LoRaSetRxPacketTimeout(500);
	if(MachType==MASTER){
		DEBUG("Master %d\r\n",MachType);
		//sprintf(MY_TEST_Msg,"Hello \r\n");
		//Radio->SetTxPacket( MY_TEST_Msg,  strlen(MY_TEST_Msg) );
		
	}else{
		DEBUG("Slave %d\r\n",MachType);
	  Radio->StartRx( );   //RFLR_STATE_RX_INIT

	}
	DEBUG("[set lora para done]\r\n");
}



__IO float voltage = 0;
__IO uint16_t raw=0;



__IO uint32_t AD_value;
__IO uint16_t input_flag;

__IO uint16_t pid_Temp1=0;
__IO uint16_t pid_Temp2=0;
__IO uint16_t pid_Temp3=0;
__IO uint16_t pid_Temp4=0;
uint8_t UART2_buffer[30];
__IO uint8_t uart2_data=0;

__IO uint8_t temp_onoff=0;
__IO uint8_t temp_flag=0;


extern uint8_t USB_Receive_Buffer[EP_SIZE];
extern u8 USB_Send_Buffer[EP_SIZE];

extern volatile uint32_t EP1_ReceivedCount;




uint8_t cmd_buffer[30];

uint8_t UART_buffer[30];
__IO uint8_t uart_data=0;

__IO uint16_t pid_ch1=0;
__IO uint16_t pid_ch2=0;

uint8_t pid_connect_flag=0;


static uint8_t bq20z95_address = 0x16;
static uint16_t v_max, v_min,v_temperature,v_percent,v_status,v_current_max,v_current_min;
static uint32_t voltage_raw,current_raw;



uint8_t update_battery_flag=0;

uint16_t OUT_Array[3] = {OUT0,OUT1,OUT2};
enum MotorDir={
	FORWARD=0,
	BACK,
	HOLD
};
void set_motor(uint8_t ch,uint8_t direction,uint16_t speed)
{
	switch (ch){
					case 0:
						if(direction==FORWARD){
							TIM4->CCR1=speed;
							TIM4->CCR2=0;
						}else if(direction==BACK){
							TIM4->CCR2=speed;
							TIM4->CCR1=0;
						}else{
							TIM4->CCR2=speed;
							TIM4->CCR1=speed;
						}
						break;
					case 1:
						if(direction==FORWARD){
							TIM3->CCR1=speed;
							TIM3->CCR2=0;
						}else if(direction==BACK){
							TIM3->CCR2=speed;
							TIM3->CCR1=0;
						}else{
							TIM3->CCR2=speed;
							TIM3->CCR1=speed;
						}
						break;
					case 2:
						if(direction==FORWARD){
							TIM3->CCR4=speed;
							TIM3->CCR3=0;
						}else if(direction==BACK){
							TIM3->CCR3=speed;
							TIM3->CCR4=0;
						}else{
							TIM3->CCR4=speed;
							TIM3->CCR3=speed;
						}
						break;
					default:
						break;
				}
}

void handle_frame(uint8_t* buf){
	uint8_t i=0;
	switch (buf[6]){
		case CMD_SET_OUTPUT_GPIO:
			DEBUG("CMD_SET_OUTPUT_GPIO %x %d %d\r\n",buf[7],OUT_Array[1],OUT1);
		
			for(i=0;i<3;i++){
				
				if((buf[7]>>i)&0x01){ DEBUG("ww\r\n");GPIO_SetBits(OUTPORT,OUT_Array[i]);}
				else	{ DEBUG("aww\r\n"); GPIO_ResetBits(OUTPORT,OUT_Array[i]);}
			}
		
			break;
		case CMD_GET_INPUT_GPIO:
				DEBUG("CMD_GET_INPUT_GPIO\r\n");
			break;
		case CMD_SET_Motor:
				DEBUG("[CMD_SET_Motor]\r\n");
				set_motor(buf[7],buf[8],(buf[9]<<8|buf[10]));
			break;
		default:
			break;
	}
}

uint8_t state=1;
void OnMaster( void );
void OnSlave( void );
/*
 * Manages the master operation
 */
uint8_t cmdID=0;
void OnMaster( void )
{
    uint8_t i;
    
    switch( Radio->Process( ) )
    {
    case RF_RX_TIMEOUT:
			DEBUG("timeout\r\n");

        // Send the next PING frame
				//Buffer[4]=cmd_buffer[4];
		if(state==1){  //先送第一台
				sprintf(Buffer,"PING");
				Buffer[4] = (ID+1)>>8;
				Buffer[5] = (ID+1);
// 				Buffer[6]=cmd_buffer[6];
//   			Buffer[7]=cmd_buffer[7];
				printf("A %d %d\r\n",Buffer[4],Buffer[5]);
        Radio->SetTxPacket( Buffer, BufferSize );   //RFLR_STATE_TX_INIT
				 for( i = 4; i < BufferSize; i++ )
        {
            Buffer[i] = 0;
        }
				cmd_buffer[4]=cmd_buffer[5]=cmd_buffer[6]=0;
			}
			
// 		if(state==2){  //再送第二台
// 				sprintf(Buffer,"PING");
// 				Buffer[4] = (ID+2)>>8;
// 				Buffer[5] = (ID+2);	
// 				printf("B %d %d\r\n",Buffer[4],Buffer[5]);
//         Radio->SetTxPacket( Buffer, BufferSize );   //RFLR_STATE_TX_INIT
// 				 for( i = 4; i < BufferSize; i++ )
//         {
//             Buffer[i] = 0;
//         }
// 				cmd_buffer[4]=cmd_buffer[5]=cmd_buffer[6]=0;
// 			}
			
			
        break;
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
				//printf("Get %s %d %d\r\n",Buffer,Buffer[4],Buffer[5]);
				if( BufferSize > 0 )
        {
					 if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 )
           {
               
							//收到第一台訊號
							
							if(ID+1==(Buffer[4]<<8|Buffer[5])){
									DEBUG("A\r\n");
									sprintf(Buffer,"PING");
									Buffer[4] = (ID+2)>>8;
									Buffer[5] = (ID+2);	
									//printf("%s %d %d\r\n",Buffer,Buffer[4],Buffer[5]);
									//
									if(cmdID==1){
										DEBUG("1\r\n");
											Buffer[6]=cmd_buffer[6];
											Buffer[7]=cmd_buffer[7];
											cmdID=0;
									}
									Radio->SetTxPacket( Buffer, BufferSize );
										memset(Buffer,0,30);
							//	while(1){};
								//	state=2;
							}
							else if(ID+2==(Buffer[4]<<8|Buffer[5])){
								DEBUG("B\r\n");
								sprintf(Buffer,"PING");
								Buffer[4] = (ID+1)>>8;
								Buffer[5] = (ID+1);	
									if(cmdID==2){
											DEBUG("2\r\n");
											Buffer[6]=cmd_buffer[6];
											Buffer[7]=cmd_buffer[7];
										cmdID=0;
									}
										Radio->SetTxPacket( Buffer, BufferSize );
										memset(Buffer,0,30);
								//printf("%s\r\n",Buffer);
									//state=3;
							}
							//Radio->SetTxPacket( Buffer, BufferSize );
						
							
						}
//             if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 6 ) == 0 )
//             {
//                 // Indicates on a LED that the received frame is a PONG
// 								GPIOA->ODR ^= (1<<0);		
// 								
//                 // Send the next PING frame            
//                 sprintf(Buffer,"PING%2x",ID+1);
// 								Buffer[6]=cmd_buffer[6];
// 								Buffer[7]=cmd_buffer[7];
// 								printf("buffer4:%d\r\n",Buffer[6]);
//                 Radio->SetTxPacket( Buffer, BufferSize );    //RFLR_STATE_TX_INIT
// 								cmd_buffer[4]=cmd_buffer[5]=cmd_buffer[6]=0;
//             }
// //             else if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
// //             { // A master already exists then become a slave
// //                 EnableMaster = false;
// // //                LedOff( LED_RED );
// //             }
// 						
						
						
        }            
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PING
				GPIOA->ODR ^= (1<<4);
        Radio->StartRx( );   //RFLR_STATE_RX_INIT
        break;
    default:
        break;
    }
}

uint8_t cmd_ping_flag=0;
void SendPing(uint16_t id)
{
	cmd_buffer[6]=0;
	cmd_buffer[7]=0;
	SendData(id);
} 
void SendData(uint16_t id)
{
	sprintf(Buffer,"PING");
	if(id==ID+1){
		Buffer[4] = (ID+1)>>8;
		Buffer[5] = (ID+1);	
	}else if(id==ID+2){
		Buffer[4] = (ID+2)>>8;
		Buffer[5] = (ID+2);	
	}
	Buffer[6]=cmd_buffer[6];
	Buffer[7]=cmd_buffer[7];
	Radio->SetTxPacket( Buffer, BufferSize );
	memset(Buffer,0,30);
}

void ParseData()
{
	switch( Radio->Process( ) )
    {
    	case RF_RX_TIMEOUT:
    		SendData(cmdID);
    		break;
    	case RF_RX_DONE:
    		Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
    		if( BufferSize > 0 )
        	{
        		if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 ){
        			DEBUG("CMD Send OK\r\n");
        			update_battery_flag=0;
        			if(cmd_ping_flag==1) cmd_ping_flag==0;
				}
        	}
    	break;
    	case RF_TX_DONE:
    		GPIOA->ODR ^= (1<<4);
        	Radio->StartRx( );   //RFLR_STATE_RX_INIT
        break;
    }
}


/*
 * Manages the slave operation
 */
void OnSlave( void )
{
    uint8_t i;

    switch( Radio->Process( ) )
    {
    case RF_RX_DONE:
        Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
				//printf("Get %d %s\r\n",BufferSize,Buffer);
        if( BufferSize > 0 )
        {
					if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4) == 0 )
					{
							//DEBUG("%d %d\r\n",ID,(Buffer[4]<<8|Buffer[5]));
							if(ID==(Buffer[4]<<8|Buffer[5]))
							{
								//DEBUG("Get %d\r\n",ID);
								handle_frame(Buffer);
							  GPIOA->ODR ^= (1<<13);
								sprintf(Buffer,"PONG");
								Buffer[6]=0;
								Buffer[7]=0;
								Radio->SetTxPacket( Buffer, BufferSize );
							}
						}
//             if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 6 ) == 0 )
//             {
// 							
// 							handle_frame(Buffer);
//                 // Indicates on a LED that the received frame is a PING
// 							
// 							if(MachType==MASTER)GPIOA->ODR ^= (1<<0);
// 							else GPIOA->ODR ^= (1<<13);

//                // Send the reply to the PONG string
//                 sprintf(Buffer,"PONG%2x",ID);
// 								printf("%s\r\n",Buffer);
//                 Radio->SetTxPacket( Buffer, BufferSize );      //RFLR_STATE_TX_INIT
//             }
        }
        break;
    case RF_TX_DONE:
        // Indicates on a LED that we have sent a PONG
//        LedToggle( LED_RED );
				if(MachType==MASTER)GPIOA->ODR ^= (1<<4);
				else GPIOA->ODR ^= (1<<13);
        Radio->StartRx( );   //RFLR_STATE_RX_INIT
        break;
    default:
        break;
    }
}


//#define SX1278_RX
#define SX1278_TX
int main(void)
{
	uint16_t i=0,j=0;
	uint8_t data[64];
	uint8_t ret;
	unsigned short a;
	uint32_t freqSx1278;
	uint32_t count=0;
	FLASH_Status FLASHStatus;
	/* Set the Vector Table base address at 0x08004000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x4000);  
	
	MachType=MMIO8(LoraSet[9].addr);
	ID=MMIO16(LoraSet[10].addr);
	bsp_init();

	if(MachType==MASTER){
		DEBUG("Master \r\n");
		BoardInit(MASTER);
		sprintf(PongMsg,"PONG%2x",ID+1);
		DEBUG("%s\r\n",PongMsg);
	}else{
		DEBUG("Slave \r\n");
		BoardInit(SLAVE);
		sprintf(PingMsg,"PING%2x",ID);
		//sprintf(PongMsg,"PONG%2x",ID);
		DEBUG("%s\r\n",PingMsg);
	TIM4->CCR1=720;
	TIM4->CCR2=00;
	
	TIM3->CCR2=500;
	TIM3->CCR1=200;
	
  	TIM3->CCR4=500;
	TIM3->CCR3=100;
	}

	
	
// 	printf("%x\r\n",I2C_ReadBytes(0x40<<1,0x0));
// 	printf("%x\r\n",I2C_ReadBytes(0x41<<1,0x0));
// 		printf("%x\r\n",I2C_ReadBytes(0x44<<1,0x0));
// 	while(1){
// 		delay_ms(100);
// 		printf("[A]%d\r\n",I2C_ReadBytes(0x40<<1,0x02));
// 		printf("[B]%d\r\n",I2C_ReadBytes(0x41<<1,0x02));
// 		printf("[C]%d\r\n",I2C_ReadBytes(0x44<<1,0x02));
// 	};
	
// while(1){
// 	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //Start ADC1 software conversion
//     while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //Wail for conversion complete
//     AD_value = ADC_GetConversionValue(ADC1); //Read ADC value
//     ADC_ClearFlag(ADC1, ADC_FLAG_EOC); //Clear EOC flag

//     printf("\r\n ADC value: %d  %3.2f\r\n", AD_value, (float)(((AD_value/4096.0)*3.3)/0.6594202898550725));
// 	delay_ms(300);
// }

//     TIM_SetCompare1(TIM4, ((100 * (4000/100))));
// TIM_SetCompare2(TIM4, ((100 * (4000/100))));
// TIM_SetCompare3(TIM4, ((100 * (4000/100))));
// TIM_SetCompare4(TIM4, ((100 * (4000/100))));


	input_flag=0;
	AD_value=0;


	

    
	
// 	
// 	for(j=0;j<TotalSettinglength;j++){
// 		DEBUG("[%d] %x\r\n",j,data[j]);
// 	}
	
		
		
     Radio = RadioDriverInit( );
	 Radio->Init( );
	 read_lora_setting_from_Flash(data);
	 set_lora_para();
	 Radio->StartRx( );
	 freqSx1278 = SX1276LoRaGetRFFrequency();

   	printf("sx1278 frequency = %d \r\n", freqSx1278);
// 		
//    		while(1){
// // 					//#if defined (SX1278_RX)
// 				OnSlave();
// // 					///#elif defined (SX1278_TX)
// 				//OnMaster();
// // 				//#endif
// 		}

// 	while(1){
// 		//#if defined (SX1278_RX)
// 		//printf("%d\r\n",Radio->Process( ));
// 		while( Radio->Process( ) == RF_RX_DONE)
// 		{
// 			Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
// 			//printf("ww\r\n");
// 			//if( strncmp( ( const char* )Buffer, ( const char* )MY_TEST_Msg, 18 ) == 0 )
// 			//{
// 				//printf("%s\r\n",Buffer);				
// 				//GPIOA->ODR ^= (1<<13);
// 				for(i=0;i<BUFFER_SIZE;i++)
// 					Buffer[i] = 0;
// 			//}
// 			Radio->StartRx( );
// 			
// 		}
// 		#elif defined (SX1278_TX)
// 		while(Radio->Process( ) == RF_TX_DONE)
// 		{
// 			printf("RF_LoRa_TX_OK!\r\n");
// 			GPIOA->ODR ^= (1<<0);
// 			Soft_delay_ms(100);
// 			 sprintf(MY_TEST_Msg,"Hello %8d\r\n",count);
// 			count++;
// 			Radio->SetTxPacket( MY_TEST_Msg, strlen(MY_TEST_Msg) );   //RFLR_STATE_TX_INIT
// 		}		
// 		#endif
//	}
	
while(1){
	if(MachType==MASTER){
		//OnMaster();
		ParseData();
	}else{
		OnSlave();
	}
	if(update_battery_flag==1 && cmd_ping_flag==0){
		SendPing(ID+1);
	}
	/*
	
	//計時器更新電池資訊
	if(update_battery_flag==1){

			for(i=0;i<50;i++){
				ADC_SoftwareStartConvCmd(ADC1, ENABLE); //Start ADC1 software conversion
				while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); //Wail for conversion complete
				AD_value += ADC_GetConversionValue(ADC1); //Read ADC value
				ADC_ClearFlag(ADC1, ADC_FLAG_EOC); //Clear EOC flag
			}
			AD_value=AD_value/50;
			//printf("ADC value: %d  %3.2f\r\n", AD_value, (float)(((AD_value/4095.0)*3.37)*4.636363636363636));
			usb_data[0]=BATTERY_CMD;	
		//電壓高16bit
	 	usb_data[2]=AD_value>>8;  			
		usb_data[3]=AD_value;
		
		USB_SendString(usb_data);
			
					
		AD_value=0;
		
		update_battery_flag=0;
		//printf("Update Battery\r\n");
	}
	if(input_flag!=0&&update_battery_flag==0){
		usb_data[0]=INTERRUPT_CMD;
		usb_data[2]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
		usb_data[3]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
		usb_data[4]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2);
		usb_data[5]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
		//printf("%x %x %x %x\r\n",usb_data[2],usb_data[3],usb_data[4],usb_data[5]);
		USB_SendString(usb_data);

		input_flag=0;
	}
*/
	if(EP1_ReceivedCount==EP_SIZE){

		printf("EP1 OUT %d %x %x %x\r\n",EP1_ReceivedCount,USB_Receive_Buffer[0],USB_Receive_Buffer[1],USB_Receive_Buffer[2]);
		
		switch (USB_Receive_Buffer[0])
		{
			case CMD_SET_LORA:
				DEBUG("[CMD_SET_LORA]\r\n");
				write_lora_setting_to_Flash(USB_Receive_Buffer+1);
				set_lora_para();
				break;
			case CMD_GET_LORA:
				DEBUG("[CMD_GET_LORA]\r\n");
				usb_data[0]=CMD_GET_LORA;
				read_lora_setting_from_Flash(data);
				memcpy(usb_data+1,data,TotalSettinglength);
				USB_SendString(usb_data);
				break;
			//Reset to Bootloader
			case CMD_RESET_TO_BOOTLOADER:
						DEBUG("[CMD_RESET_BOARD]\r\n");
						FLASH_Unlock();
						FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR); 
						FLASHStatus = FLASH_ErasePage(UpdateAddress);
					 
						if(FLASHStatus == FLASH_COMPLETE)
						{
							FLASHStatus = FLASH_ProgramWord(UpdateAddress, UPDATE_CODE);
						}
						delay_ms(200);
						NVIC_SystemReset();
				break;
				case CMD_SET_OUTPUT_GPIO:
					//OUTPUT 控制
				DEBUG("[CMD_SET_OUTPUT_GPIO]\r\n");
				printf("%x %x %x %x \r\n",USB_Receive_Buffer[1],USB_Receive_Buffer[2],USB_Receive_Buffer[3],USB_Receive_Buffer[4]);
				cmd_buffer[4]=USB_Receive_Buffer[1];
				cmd_buffer[5]=USB_Receive_Buffer[2];
				cmd_buffer[6]=CMD_SET_OUTPUT_GPIO;
				cmd_buffer[7]=USB_Receive_Buffer[3];
				if((USB_Receive_Buffer[1]<<8|USB_Receive_Buffer[2])==ID+1){
					cmdID=1;
					cmd_ping_flag=1;
					SendData(cmdID);
				
				}else if((USB_Receive_Buffer[1]<<8|USB_Receive_Buffer[2])==ID+2){
					cmdID=2;
					cmd_ping_flag=1;
					SendData(cmdID);

				}
					break;
				case CMD_GET_INPUT_GPIO:
				DEBUG("[CMD_GET_INPUT]\r\n");
				printf("%x %x %x %x\r\n",USB_Receive_Buffer[1],USB_Receive_Buffer[2],USB_Receive_Buffer[3],USB_Receive_Buffer[4]);
				usb_data[0]=READ_INPUT_CMD;
				usb_data[2]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
				usb_data[3]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
				usb_data[4]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2);
				usb_data[5]=!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10);
				//printf("%x %x %x %x\r\n",usb_data[2],usb_data[3],usb_data[4],usb_data[5]);
				USB_SendString(usb_data);
					break;
				case CMD_SET_Motor:
					DEBUG("[CMD_SET_Motor]\r\n");
					cmd_buffer[4]=USB_Receive_Buffer[1];
					cmd_buffer[5]=USB_Receive_Buffer[2];
					cmd_buffer[6]=CMD_SET_Motor;
					cmd_buffer[7]=USB_Receive_Buffer[3];
					if((USB_Receive_Buffer[1]<<8|USB_Receive_Buffer[2])==ID+1){
						cmdID=1;
						cmd_ping_flag=1;
						SendData(cmdID);
					
					}else if((USB_Receive_Buffer[1]<<8|USB_Receive_Buffer[2])==ID+2){
						cmdID=2;
						cmd_ping_flag=1;
						SendData(cmdID);
	
					}
					break;
			default:
				break;
		}
	
		
		EP1_ReceivedCount=0;
	}
	  
}

}


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif

/*********************************END OF FILE**********************************/
