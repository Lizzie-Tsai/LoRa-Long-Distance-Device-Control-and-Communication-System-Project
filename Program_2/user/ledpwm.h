#include "stm32f10x.h"

#define LED_MAXPWM 520

void LEDPWMInit(void);
void LEDSetPWM(uint16_t LED_PWM);
uint16_t LEDGetPWM(void);

void IOInit(void);
void set_12V_relay_on(uint8_t ch);
void set_12V_relay_off(uint8_t ch);
void set_3V3_trigger_on(uint8_t ch);
void set_3V3_trigger_off(uint8_t ch);
void set_110V_relay_off(uint8_t ch);
void set_110V_relay_on(uint8_t ch);
#define _12V_CH1_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_14)
#define _12V_CH1_OFF                      GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define _12V_CH2_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_15)
#define _12V_CH2_OFF                      GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define _12V_CH3_ON                     	GPIO_ResetBits(GPIOC,GPIO_Pin_14)
#define _12V_CH3_OFF                      GPIO_SetBits(GPIOC,GPIO_Pin_14)

#define _12V_CH4_ON                     	GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define _12V_CH4_OFF                      GPIO_SetBits(GPIOC,GPIO_Pin_13)

#define _12V_CH5_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_11)
#define _12V_CH5_OFF                      GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define _12V_CH6_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define _12V_CH6_OFF                      GPIO_SetBits(GPIOB,GPIO_Pin_10)

#define _12V_CH7_ON                     	GPIO_ResetBits(GPIOA,GPIO_Pin_10)
#define _12V_CH7_OFF                      GPIO_SetBits(GPIOA,GPIO_Pin_10)

#define _12V_CH8_ON                     	GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define _12V_CH8_OFF                      GPIO_SetBits(GPIOA,GPIO_Pin_8)


#define _110V_CH1_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_12)
#define _110V_CH1_OFF                     GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define _110V_CH2_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_13)
#define _110V_CH2_OFF                     GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define _110V_CH3_ON                     	GPIO_ResetBits(GPIOA,GPIO_Pin_0)
#define _110V_CH3_OFF                     GPIO_SetBits(GPIOA,GPIO_Pin_0)

#define _110V_CH4_ON                     	GPIO_ResetBits(GPIOC,GPIO_Pin_15)
#define _110V_CH4_OFF                     GPIO_SetBits(GPIOC,GPIO_Pin_15)

#define _3V3V_CH5_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_2)
#define _3V3V_CH5_OFF                     GPIO_SetBits(GPIOB,GPIO_Pin_2)

#define _3V3V_CH6_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_1)
#define _3V3V_CH6_OFF                     GPIO_SetBits(GPIOB,GPIO_Pin_1)

#define _3V3V_CH7_ON                     	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define _3V3V_CH7_OFF                     GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define _3V3V_CH8_ON                     	GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define _3V3V_CH8_OFF                     GPIO_SetBits(GPIOA,GPIO_Pin_7)
