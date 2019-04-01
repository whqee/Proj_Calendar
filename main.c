#include <common.h>
#include <lcd1602.h>
#include <ds1302.h>
<<<<<<< HEAD
=======

#define BCD_TO_BIN(val)   ( (((val) >> 4) * 10) +  ((val)&15) )    // Applicable to 8 'bit data length
#define BIN_TO_BCD(val)   ( (((val)/10) << 4) + (((val)%10)) )	   // Applicable to 8 'bit data length
>>>>>>> dev

sbit KEY0 = P3^2;
sbit KEY1 = P3^3;

// Variable definition:
u8 i = 0, xdata tmp;  // temporary 'data
static u8 xdata count = 0;  // running flag for KEY0_Line Interrupt 0
static u8 xdata pm = 0;  // define for am pm
static u8 xdata Enable_12_hour_display = 0xff;
static char xdata time_now[7];
static char time_ascii[14];

//functions prototype:
static void print_time();
void check_time();
void update_time_for_set_time(u8 x,u8 y,u8 t,u8 count_copy);
void delay_50ms();


void main()
{
	EA = 0;	// Disable Interrupt
	lcd1602_Init();	
	
	/** KEY_Init: Set KEY0 Interrupt **/
	IT0 = 1;			// KEY0 Falling edge trigger
	IT1 = 1;			// KEY1 Falling edge trigger
	EX0 = 1;			// Enable KEY0 Interrupt line
	EX1 = 0;
	EA = 1;				// Enable Interrupt
	/** End setting KEY0 Interrupt **/
	
	while(1)
	{
		Normal_Running:
		if(count)
			goto Set_Time;
		
		ds1302_read_time(time_now);
<<<<<<< HEAD
=======
		check_time();
>>>>>>> dev
		print_time();
	}
	while(1)
	{
		Set_Time:
		if(!count)
			goto Normal_Running;

		while (count) {
			switch (count) {
			case 1:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 59) tmp = 0;	//modify here         1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				update_time_for_set_time(6,1,5,count);   // Modify here  2
				break;
			case 2:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 59) tmp = 0;	//modify here         1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				update_time_for_set_time(3,1,5,count);   // Modify here  2
				break;
			case 3:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 23) tmp = 0;	//modify here          1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				if (Enable_12_hour_display) {
					if (BCD_TO_BIN(time_now[2]) > 12 ) {
						tmp = BIN_TO_BCD(BCD_TO_BIN(time_now[2]) - 12);
						lcd1602_show_str(0,1, &tmp, 2);
					} else
					{
						lcd1602_show_str(0,1, &tmp, 2);
					}
				}
				update_time_for_set_time(0,1,5,count);   // Modify here  2
				break;
			case 4:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 7) tmp = 1;	//modify here             1 
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				// update display'
				EA = 0; // Disable Interrupt
				lcd1602_show_str(10,0, "  ", 2);  // modify here (x,y)           2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII.
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII.
				switch ((time_now[3] & 15)) {             //modify here  (x,y)                 3-8
				case 1:
					lcd1602_show_str(11,0, "1 Mon", 5); break;
				case 2:
					lcd1602_show_str(11,0, "2 Tue", 5); break;
				case 3:
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
					lcd1602_show_str(11,0, "error", 5);
					break;
				}
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			case 5:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 31) tmp = 1;	//modify here                 1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				update_time_for_set_time(8,0,5,count);   // Modify here  2
				break;
			case 6:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 12) tmp = 1;	//modify here            1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				update_time_for_set_time(5,0,5,count);   // Modify here  2
				break;
			case 7:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 99) tmp = 0;     // modify here         1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				update_time_for_set_time(2,0,5,count);   // Modify here  2
				break;
			case 8:
				if (KEY1 == 0) Enable_12_hour_display = ~Enable_12_hour_display;
				if (Enable_12_hour_display) {
					if (pm) {
						lcd1602_show_str(9,1, "pm", 2);
					} else
					{
						lcd1602_show_str(9,1, "am", 2);
					}
				} else
				{
					lcd1602_show_str(9,1, "  ", 2);
				}
				
				for(i=4; i > 0; i--) delay_50ms();
				lcd1602_show_str(9,1, "  ", 2);
				for(i=4; i > 0; i--) delay_50ms();
				break;
			default:
				lcd1602_show_str(11,0, "error", 5);
				break;
			}
		}
		ds1302_set_time(time_now);
	}
	
}


void print_time()
{
	u8 j = 7, x = 2, y =0;
	lcd1602_show_str(0,0, "20", 2);
	while(j--)
	{
		// BCD_TO_ASCII
		time_ascii[2*j+1] = time_now[j] & 63 | 48;
		time_ascii[2*j] = time_now[j] >>4 &63 | 48;

		// print: year.mon.date
		if (j > 3) {
			lcd1602_show_str(x,y, &time_ascii[2*j], 2);
			x += 2;
			if (x > 8) 
				lcd1602_show_str(x,y, " ", 1);
			else
				lcd1602_show_str(x,y, ".", 2);
			x += 1;

			
		}

		//print: day
		if (j == 3) {
			switch ((time_now[j] & 15)) {
			case 1:
				lcd1602_show_str(x,y, "1 Mon", 5); break;
			case 2:
				lcd1602_show_str(x,y, "2 Tue", 5); break;
			case 3:
				lcd1602_show_str(x,y, "3 Wed", 5); break;
			case 4:
				lcd1602_show_str(x,y, "4 Thu", 5); break;
			case 5:
				lcd1602_show_str(x,y, "5 Fri", 5); break;
			case 6:
				lcd1602_show_str(x,y, "6 Sat", 5); break;
			case 7:
				lcd1602_show_str(x,y, "7 Sun", 5); break;
			default:
				ds1302_set_time_once(j, 1);
				lcd1602_show_str(x,y, "error", 5);
				break;
			}
			x = 0;
			y = 1;
		}
		
		// print: hours:min:sec
		if (j < 3) {
			lcd1602_show_str(x,y, &time_ascii[2*j], 2);
			x += 2;
			if (x < 6)
				lcd1602_show_str(x,y, ":", 1);
			x += 1;				
		}
		
		
	}
	// lcd1602_print(time_ascii);
	
}


void check_time()
{
	if (BCD_TO_BIN(time_now[5]) ==  4 | 6 | 8 | 11 && BCD_TO_BIN(time_now[4] > 30)) {
			time_now[4] = 1;
			time_now[5] += 1;
			ds1302_set_time_once(5, time_now[5]);
			ds1302_set_time_once(4, time_now[4]);
	}
	if (BCD_TO_BIN(time_now[5]) == 2 && BCD_TO_BIN(time_now[4] > 28)) {
		if (! BCD_TO_BIN(time_now[6]) % 4) {
			time_now[4] = 1;
			time_now[5] += 1;
			ds1302_set_time_once(5, time_now[5]);
			ds1302_set_time_once(4, time_now[4]);
		}
	}
	if (Enable_12_hour_display) {
		if (BCD_TO_BIN(time_now[2]) > 12 ) {
			pm = 1;
			time_now[2] = BIN_TO_BCD(BCD_TO_BIN(time_now[2]) - 12);
			lcd1602_show_str(9,1, "pm", 2);
		} else
		{
			lcd1602_show_str(9,1, "am", 2);
		}
	}
}


void update_time_for_set_time(u8 x,u8 y,u8 t,u8 count_copy)
{
	// update display
	EA = 0; // Disable Interrupt
	lcd1602_show_str(x,y, "  ", 2);  // modify here (x,y)          2
	for(i = t; i > 0; i--) delay_50ms();
	time_ascii[2*count_copy-1] = time_now[count_copy-1] & 63 | 48;    // BCD TO ASCII.
	time_ascii[2*count_copy-2] = time_now[count_copy-1] >>4 &63 | 48; // BCD TO ASCII.
	lcd1602_show_str(x,y, &time_ascii[2*count_copy-2], 2); // modify here (x,y)           3
	EA = 1;		//Enable Interrupt
	for(i = t; i > 0; i--) delay_50ms();
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
	delay_50ms();	//  Be adopted to prevent dithering and repeated actions
	if (KEY0 == 0) {
		if(!count)
			count = 8;
		else 
			count--;

		for(i=11; i > 0; i--)
			delay_50ms();
	}
}


