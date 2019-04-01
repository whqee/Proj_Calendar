#include "lcd1602.h"



sbit lcd1602_E	 = P2^7;			
sbit lcd1602_RW = P2^6;			
sbit lcd1602_RS = P2^5;			

// Internal functions prototype:
static void delay5ms(void);
static void lcd1602_wait_noBusy(void);
static void lcd1602_write_cmd(u8 cmd);
static void lcd1602_write_data(u8 dat);



static void lcd1602_wait_noBusy(void)  
{
    u8 sta = 0;      //

    LCD1602_DATA_PORT = 0xff;
    lcd1602_RS = 0;
    lcd1602_RW = 1;
    do
    {
        lcd1602_E = 1;
        sta = LCD1602_DATA_PORT;
        lcd1602_E = 0;    
    }while(sta & 0x80);
}

static void lcd1602_write_cmd(u8 cmd)	  
{
	lcd1602_wait_noBusy();		

	lcd1602_E = 0;     		
	lcd1602_RS = 0;	   		
	lcd1602_RW = 0;	   		
	LCD1602_DATA_PORT = cmd;    
	lcd1602_E = 1;	          	
	lcd1602_E = 0;				
}

static void lcd1602_write_data(u8 dat)			
{
	lcd1602_wait_noBusy();		

	lcd1602_E = 0;     		
	lcd1602_RS = 1;	   		
	lcd1602_RW = 0;	   		
	LCD1602_DATA_PORT = dat;   
	lcd1602_E = 1;	          	
	lcd1602_E = 0;				
}

void lcd1602_Init(void)						
{
 	lcd1602_write_cmd(0x38);  	
	delay5ms();					
	lcd1602_write_cmd(0x38);  	
	delay5ms();					
	lcd1602_write_cmd(0x38);  	
	delay5ms();					
	lcd1602_write_cmd(0x38);		
	lcd1602_write_cmd(0x08);		
	lcd1602_write_cmd(0x01);		
	lcd1602_write_cmd(0x06);		
	lcd1602_write_cmd(0x0c);		
}




void lcd1602_set_cursor(u8 x, u8 y)  
{
    u8 addr = 0;

   	switch (y)
	{
		case 0:	 					
			addr = 0x00 + x;		break;	
		case 1:						
			addr = 0x40 + x; 		break;
		default:
									break;
	}
    lcd1602_write_cmd(addr | 0x80);
}

void lcd1602_show_str(u8 x, u8 y, u8 *pStr, u8 size)     
{
    lcd1602_set_cursor(x, y);      
    while (size--)
    {
        lcd1602_write_data(*pStr++);
    }
}

// void lcd1602_print(u8 *pStr)     
// {
// 	u8 x = 0;
//     lcd1602_set_cursor(x, 0);      
//     while (*pStr != '\0')
//     {
//         lcd1602_write_data(*pStr++);
// 			if(x++ == 15)
// 				lcd1602_set_cursor(0, 1);
//     }
// }


static void delay5ms(void)   
{
    unsigned char a,b;
    for(b=19;b>0;b--)
        for(a=130;a>0;a--);
}  


























