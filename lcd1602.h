#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "common.h"

#define LCD1602_DATA_PORT	 P0			// LCD1602的8位数据端口



void lcd1602_Init(void);
void lcd1602_set_cursor(u8 x,u8 y);
void lcd1602_show_str(u8 x, u8 y, u8 *pStr, u8 size);
void lcd1602_print(u8 *pStr);

#endif
