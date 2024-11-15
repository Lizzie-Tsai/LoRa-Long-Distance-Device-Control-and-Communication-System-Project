
#ifndef _BSP_H
#define _BSP_H
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stm32f10x.h>
#include "delay.h"
#include "usart.h"
#include "ledpwm.h"
#include "adc.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_io.h"
#include "usb_desc.h"
#include "smbus.h"

#include "i2c.h"
#define OUTPORT GPIOA
#define OUT0 GPIO_Pin_2
#define OUT1 GPIO_Pin_3
#define OUT2 GPIO_Pin_15

#define IN0PORT GPIOA
#define INPORT GPIOB
#define IN0 GPIO_Pin_0
#define IN1 GPIO_Pin_2
#define IN2 GPIO_Pin_12
#define IN3 GPIO_Pin_13
#define IN4 GPIO_Pin_14
#define IN5 GPIO_Pin_15
#define IN6 GPIO_Pin_3
#define IN7 GPIO_Pin_11
#define IN8 GPIO_Pin_10

void bsp_init(void);
#endif /*_BSP_H*/

/*********************************END OF FILE**********************************/
