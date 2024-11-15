/*
 * THE FOLLOWING FIRMWARE IS PROVIDED: (1) "AS IS" WITH NO WARRANTY; AND 
 * (2)TO ENABLE ACCESS TO CODING INFORMATION TO GUIDE AND FACILITATE CUSTOMER.
 * CONSEQUENTLY, SEMTECH SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION
 * CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 * 
 * Copyright (C) SEMTECH S.A.
 */
/*! 
 * \file       spi.c
 * \brief      SPI hardware driver
 *
 * \version    1.0
 * \date       Feb 12 2010
 * \author     Miguel Luis
 */
 
//#include "stm32f10x_spi.h"

#include "spisx1278.h"


//ÐÞ¸Ä³ÉSPI1
#define SPI_INTERFACE                               SPI1
// #define SPI_CLK                                     RCC_APB2Periph_SPI1

// #define SPI_PIN_SCK_PORT                            GPIOB
// #define SPI_PIN_SCK_PORT_CLK                        RCC_APB2Periph_GPIOB
// #define SPI_PIN_SCK                                 GPIO_Pin_3

// #define SPI_PIN_MISO_PORT                           GPIOB
// #define SPI_PIN_MISO_PORT_CLK                       RCC_APB2Periph_GPIOB
// #define SPI_PIN_MISO                                GPIO_Pin_4

// #define SPI_PIN_MOSI_PORT                           GPIOB
// #define SPI_PIN_MOSI_PORT_CLK                       RCC_APB2Periph_GPIOB
// #define SPI_PIN_MOSI                                GPIO_Pin_5


void SpiInit( uint8_t type )
{

		//SPI_Configuration(type);
}

uint8_t SpiInOut( uint8_t outData )
{
	uint8_t ret;
	uint8_t retemp;
  ret=HAL_SPI_TransmitReceive(&SpiHandle,&outData,&retemp,1,100);
	//printf("ret %d %x\r\n",ret,retemp);
  return retemp;
}

