#include <common.h>
#include <lcd1602.h>
#include <ds1302.h>

sbit KEY0 = P3^2;
sbit KEY1 = P3^3;


u8 i = 0, k;
static u8 count = 0;
static char time_now[7];
static char time_ascii[14];

//functions prototype:
static void print_time();
void delay_50ms();


void main()
{
	EA = 0;
	lcd1602_Init();	
	
	/** KEY_Init: Set KEY0 Interrupt **/
	IT0 = 1;			// Falling edge trigger
	EX0 = 1;			// Enable EX0 Interrupt line
	IT1 = 1;
	EX1 = 0;
	EA = 1;				// Enable Interrupt
	/** End setting KEY0 Interrupt **/
	
	while(1)
	{
		Normal_Running:
		if(count)
			goto Set_Time;
		
		ds1302_read_time(time_now);
		print_time();
	}
	while(1)
	{
		Set_Time:
		if(!count)
			goto Normal_Running;
		while (count) {
			switch (count) {
				case 13:
					k = 12;
					time_ascii[k] = time_now[k/2] >>4 & 63 | 48;  lcd1602_show_str(2,0, &time_ascii[k], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 16;  if((time_now[k/2]>>4) > 9) time_now[k/2] &= 15;
				break;
				case 12:
					k = 12;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(3,0, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 9) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;

				case 11:
					k = 8;
					time_ascii[k] = time_now[k/2] >>4 & 63 | 48;  lcd1602_show_str(5,0, &time_ascii[k], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 16;  if((time_now[k/2]>>4) > 1) time_now[k/2] &= 15;
				break;
				case 10:
					k = 8;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(6,0, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 9) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;

				case 9:
					k = 6;
					time_ascii[k] = time_now[k/2] >>4 & 63 | 48;  lcd1602_show_str(8,0, &time_ascii[k], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 16;  if((time_now[k/2]>>4) > 3) time_now[k/2] &= 15;
				break;
				case 8:
					k = 6;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(9,0, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 9) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;

				case 7:
					k = 10;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(11,0, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 7) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;

				case 6:
					k = 4;
					time_ascii[k] = time_now[k/2] >>4 & 63 | 48;  lcd1602_show_str(0,1, &time_ascii[k], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 16;  if((time_now[k/2]>>4) > 2) time_now[k/2] &= 15;
				break;
				case 5:
					k = 4;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(1,1, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 9) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;

				case 4:
					k = 2;
					time_ascii[k] = time_now[k/2] >>4 & 63 | 48;  lcd1602_show_str(3,1, &time_ascii[k], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 16;  if((time_now[k/2]>>4) > 6) time_now[k/2] &= 15;
				break;
				case 3:
					k = 2;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(4,1, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 9) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;

				case 2:
					k = 0;
					time_ascii[k] = time_now[k/2] >>4 & 63 | 48;  lcd1602_show_str(6,1, &time_ascii[k], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 16;  if((time_now[k/2]>>4) > 6) time_now[k/2] &= 15;
				break;
				case 1:
					k = 0;
					time_ascii[k] = time_now[k/2] & 63 | 48;  lcd1602_show_str(7,1, &time_ascii[k+1], 1); 
					for(i=11; i > 0; i--)delay_50ms();  if(KEY1 == 0) time_now[k/2] += 1;  if(time_now[k/2] & 15 > 9) time_now[k/2] &= 240; // 240 is 1111 0000b
				break;
			}
			ds1302_set_time(time_now);
		}
		//time_now[0] = 0x50;
		//time_now[1] = 0x59;
		//time_now[2] = 0x23;
		//time_now[3] = 0x23;
		//time_now[4] = 0x10;
		//time_now[5] = 0x01;
		//time_now[6] = 0x17;
		//ds1302_set_time(time_now);
	}
	
}


static void print_time()
{
	u8 j = 7;
	while(j--)
	{
		time_ascii[2*j+1] = time_now[j] & 63 | 48;
		time_ascii[2*j] = time_now[j] >>4 &63 | 48;
	}

	lcd1602_show_str(0,0, "20", 2);
	lcd1602_show_str(2,0, &time_ascii[12], 2);
	lcd1602_show_str(4,0, ".", 1);
	lcd1602_show_str(5,0, &time_ascii[8], 2);
	lcd1602_show_str(7,0, ".", 1);
	lcd1602_show_str(8,0, &time_ascii[6], 2);
		
	lcd1602_show_str(0,1, &time_ascii[4], 2);
	lcd1602_show_str(2,1, ":", 1);
	lcd1602_show_str(3,1, &time_ascii[2], 2);
	lcd1602_show_str(5,1, ":", 1);
	lcd1602_show_str(6,1, &time_ascii[0], 2);
		
	switch ((time_ascii[11] & 15)) {
		case 0x1:
			lcd1602_show_str(11,0, "1 Mon", 5); break;
		case 0x2:
			lcd1602_show_str(11,0, "2 Tue", 5); break;
		case 0x3:
			lcd1602_show_str(11,0, "3 Wed", 5); break;
		case 4:
			lcd1602_show_str(11,0, "4 Thu", 5); break;
		case 5:
			lcd1602_show_str(11,0, "5 Fri", 5); break;
		case 6:
			lcd1602_show_str(11,0, "6 Sat", 5); break;
		case 7:
			lcd1602_show_str(11,0, "7 Sun", 5); break;
		default:
			lcd1602_show_str(11,0, &time_ascii[11], 1); break;
	}
}

void delay_50ms()
{
	unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void KEY_Line() interrupt 0
{
	u8 i = 0;
	delay_50ms();
	if(!count)
		count = 13;
	else 
		count--;

	for(i=11; i > 0; i--)
			delay_50ms();
}


