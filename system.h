#ifndef __SYSTEM_H_
#define __SYSTEM_H_

#include <STC/STC89C5xRC.h>
#include <common.h>
#define T_INIT_VALUE 0x9c  //0.1ms

extern u16 tick;


static void Timer_Init();
extern void delay_ms(u8 t);
static void Timer1_Interrupt();



#endif
