#ifndef __SCHEDULER_H_
#define __SCHEDULER_H_

#include <system.h>


static unsigned int Scheduler_Stack[25];
typedef struct timer{
	unsigned char flag;
	unsigned long tick;
} Timer;

Timer xdata timer_list[48] = 0;


void Scheduler_Init();
void sch_delay(unsigned int tick);


#define SCH_Delay(x); \
									t_ptr = &timer_list[0]; \
									while((*t_ptr)->flag) \
										t_ptr++; \
									(*t_ptr)->flag = 1; \
									(*t_ptr)->tick =  x;

#define Sch_delay(x); \
									SCH_Delay(x); \
									#ifndef T1	\
									#define T1	\
									
									T1:








#endif
