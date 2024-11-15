#include "stm32f10x.h"

#define SMBus_NAME             I2C2
#define SMBus_RCC_Periph       RCC_APB1Periph_I2C2
#define SMBus_Port             GPIOB
#define SMBus_SCL_Pin          GPIO_Pin_10
#define SMBus_SDA_Pin          GPIO_Pin_11
#define SMBus_SCL_PinSource    GPIO_PinSource10
#define SMBus_SDA_PinSource    GPIO_PinSource11
#define SMBus_RCC_Port         RCC_APB2Periph_GPIOB
#define SMBus_Speed            12000
#define SMBus_GPIO_AF          GPIO_AF_I2C2
#define SMBus_Max_Delay_Cycles 100000

extern void SMBus_init();
extern void SMBus_WriteWord(uint8_t slaveAddr, uint16_t data, uint8_t WriteAddr);
extern uint8_t SMBus_ReadByte(uint8_t slaveAddr, uint8_t readAddr);
extern uint8_t SMBus_ReadWord(uint8_t slaveAddr, uint16_t* data, uint8_t ReadAddr);
extern void SMBus_WriteBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
extern void SMBus_WriteBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t data);
extern void SMBus_ReadBits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);
extern void SMBus_ReadBit(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitNum, uint8_t *data);
extern uint8_t SMBus_CRC8(uint32_t data);
