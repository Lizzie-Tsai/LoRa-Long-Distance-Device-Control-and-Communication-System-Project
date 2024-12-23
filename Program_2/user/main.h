#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f10x_conf.h"

enum MACH_TYPE{
	MASTER=0,
	SLAVE
};

enum CMD_TYPE{
	SET_PWM = 0,
	GET_PWM,
	CMD_WRITE_LIQLENS,
	CMD_READ_LIQLENS,
	CMD_SET_MACH_TYPE,
	CMD_GET_BOOT_INFO_SN,
	CMD_RESET_TO_BOOTLOADER=8,
	CMD_ERASE_AND_UPDATE_APP,
	CMD_COMPLETE_UPDATE,
	CMD_SET_OUTPUT_GPIO,
	CMD_GET_OUTPUT_GPIO,
	CMD_GET_INPUT_GPIO,
	CMD_SET_LORA,
	CMD_GET_LORA,
	CMD_SET_Motor,
	CMD_GET_Motor,
	CMD_SET_Current,
	CMD_GET_Current,

};



#endif/* __MAIN_H */

