#include "stm32f10x.h"

#define DLL_ADDR      0xB4

#define DLL_REG_CONFIG 0x00
#define DLL_REG_BSTREF_SEL_AB 0x01
#define DLL_REG_VBO_SEL 0x02
#define DLL_REG_FREQ_SEL 0x03
#define DLL_REG_ENABLE_PWM 0x04
#define DLL_REG_PWM_PHASE 0x06

#define DLL_FREQ_SEL_0K5 0
#define DLL_FREQ_SEL_1K0 1
#define DLL_FREQ_SEL_10K 2
#define DLL_FREQ_SEL_50K 3

void DLL_Test(void);
