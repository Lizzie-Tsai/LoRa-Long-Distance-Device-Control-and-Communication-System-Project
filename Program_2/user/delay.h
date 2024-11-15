#include "stm32f10x.h"

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
//void Delay(unsigned long delay_time);
void Soft_delay_ms(u16 time);
void Soft_delay_us(u16 time);