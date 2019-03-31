#ifndef __DS1302_H__
#define __DS1302_H__

#include "common.h"


// External Interface
void ds1302_set_time(u8 time[7]); //0-7:  s,min,hours,date,month,day,year
void ds1302_read_time(u8 temp[7]); 



#endif