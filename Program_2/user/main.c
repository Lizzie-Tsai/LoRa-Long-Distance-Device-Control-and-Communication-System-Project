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
#define BUFFER_SIZE     20   // Define the payload size here

static uint16_t BufferSize = BUFFER_SIZE;	 // RF buffer size
static uint8_t  Buffer[BUFFER_SIZE];		// RF buffer

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

uint8_t MachType=0;
uint16_t ID=0;

extern uint8_t USB_Receive_Buffer[EP_SIZE]; //64
extern u8 USB_Send_Buffer[EP_SIZE];
extern volatile uint32_t EP1_ReceivedCount;
uint8_t cmd_buffer[BUFFER_SIZE];

void OnMaster( void );
void read_lora_setting_from_Flash(uint8_t* data);
void write_lora_setting_to_Flash(uint8_t* data);
void set_lora_para();

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
	MachType=MASTER;
	BoardInit(MASTER);

	Radio = RadioDriverInit( );
	Radio->Init( );
	read_lora_setting_from_Flash(data);
	set_lora_para();
	Radio->SetTxPacket( PingMsg, 4 );

	freqSx1278 = SX1276LoRaGetRFFrequency();
	printf("sx1278 frequency = %d \r\n", freqSx1278);
	while(1){
		OnMaster();
		if(EP1_ReceivedCount==EP_SIZE){
			DEBUG("EP1 OUT %d %x %x %x\r\n",EP1_ReceivedCount,USB_Receive_Buffer[0],USB_Receive_Buffer[1],USB_Receive_Buffer[2]);
			/** Recieved Message from USB 
					*     index: [              0,          1,       2,...,             9,    10,    11,          12,...64]
				  *   content: [  CMD_SET_Motor, LED ON/OFF, LED num,..., Buzzer ON/OFF, LCD x, LCD y, LCD content,.....]
					*/
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
				/* Reset to Bootloader */
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
				case CMD_SET_Motor:
					DEBUG("[CMD_SET_Motor] %x %x 111\r\n",USB_Receive_Buffer[1],USB_Receive_Buffer[2]);
				  /* Fill cmd_buffer with USB_Receive_Buffer */
					memcpy(cmd_buffer+4,USB_Receive_Buffer+1,16);
					break;
				case CMD_GET_INPUT_GPIO:
					usb_data[0]=CMD_GET_INPUT_GPIO;
					usb_data[6]=	cmd_buffer[6];
					usb_data[7]=	cmd_buffer[7];
				  /* USB Send */
					USB_SendString(usb_data);
				break;
				default:
					break;
			}
			EP1_ReceivedCount=0;
		}
	}
}
/**
  * @brief LoRa Tx/Rx Tasks
  * @retval None
  */
void OnMaster( void )
{
	uint8_t i;
	switch( Radio->Process( ) )
	{
	case RF_RX_TIMEOUT:
		/* Send the PING frame */
		Buffer[0] = 'P';
		Buffer[1] = 'I';
		Buffer[2] = 'N';
		Buffer[3] = 'G';
		Radio->SetTxPacket( Buffer, 20 );   // RFLR_STATE_TX_INIT
		break;
	case RF_RX_DONE:
		Radio->GetRxPacket( Buffer, ( uint16_t* )&BufferSize );
		/** Recieved Message from LoRa 
			*     index: [  0,   1,   2,   3, 4, 5,     6,     7,    8,    9,   10,   11, ..20]
			*   content: ['P', 'O', 'N', 'G', X, X, TempL, TempH, Key0, Key1, Key2, Key3, ....]
			*/
	  if( BufferSize > 0 )
		{
			if( strncmp( ( const char* )Buffer, ( const char* )PongMsg, 4 ) == 0 )
			{
			  printf("Get PONG\r\n");
				/* Indicates on a LED that the received frame is a PONG */
				GPIOA->ODR ^= (1<<4);
				/* Send the PING frame as reply */
				Buffer[0] = 'P';
				Buffer[1] = 'I';
				Buffer[2] = 'N';
				Buffer[3] = 'G';

				/* Set usb_data */
				usb_data[0]=CMD_GET_INPUT_GPIO;
				/** Message send to USB
					*     index: [                 0,   1,   2,   3, 4, 5,     6,     7,    8,    9,   10,   11, ..20]
				  *   content: [CMD_GET_INPUT_GPIO,   X,   X,   X, X, X, TempL, TempH, Key0, Key1, Key2, Key3, ....]
					*/
				memcpy(usb_data+6,Buffer+6,14);
				/* USB Send */
				USB_SendString(usb_data);
			
				/* Fill Buffer with cmd_buffer */
				/** Message Sent to LoRa 
					*     index: [  0,   1,   2,   3,             4,       5,                12,    13,    14,          15,...20]
					*   content: ['P', 'I', 'N', 'G',    LED ON/OFF, LED num,..., Buzzer ON/OFF, LCD x, LCD y, LCD content,.....]
					*/
				memcpy(Buffer+4,cmd_buffer+4,16);
				/* LoRa Send */
				Radio->SetTxPacket( Buffer, 20 );    // RFLR_STATE_TX_INIT
			}
			else if( strncmp( ( const char* )Buffer, ( const char* )PingMsg, 4 ) == 0 )
			{   
				/* A master already exists then become a slave */
				EnableMaster = false;
			}
		}            
		break;
	case RF_TX_DONE:
		/* Indicates on a LED that we have sent a PING */
		printf("Sent PING\r\n");
		GPIOA->ODR ^= (1<<5);
		Radio->StartRx( );   //RFLR_STATE_RX_INIT
		break;
	default:
		break;
	}
}

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
	SX1276LoRaSetRxPacketTimeout(MMIO16(LoraSet[7].addr));
	//SX1276LoRaSetRxPacketTimeout(500);
	//SX1276LoRaSetRxSingleOn(0);
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


#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif

/*********************************END OF FILE**********************************/
