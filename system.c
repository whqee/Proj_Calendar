#include <system.h>

u16 tick = 0;

static void Timer1_Init()
{
	TMOD |= 0x60; //set T1 mode 2
	TL1 = 0x9c;
	TH1 = 0x9c;
	ET1 = 1; //Enable Timer 1 IRQ
	EA = 1; //Enable all IRQ
	TR1 = 1; //Timer 1 start
}

void delay_ms(u8 t)
{
	tick = t*10 - 1;
	while(tick);
}

void Timer1_Interrupt() interrupt 1
{
	if(tick)
		tick--;
}
