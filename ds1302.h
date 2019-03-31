#ifndef __DS1302_H__
#define __DS1302_H__

#include "common.h"


// External Interface
void ds1302_set_time(u8 time[7]); //0-6:  sec,min,hours,day,date,mon,year
void ds1302_read_time(u8 temp[7]); 
void ds1302_set_time_once(u8 write_addr_num, u8 t); //write_addr_num: 0-6: sec,min,hours,day,date,mon,year


#endif
