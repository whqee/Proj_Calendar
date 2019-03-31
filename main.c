#include <common.h>
#include <lcd1602.h>
#include <ds1302.h>

#define BCD_TO_BIN(val)   ( (((val) >> 4) * 10) +  ((val)&15) )
#define BIN_TO_BCD(val)   ( (((val)/10) << 4) + (((val)%10)) )

sbit KEY0 = P3^2;
sbit KEY1 = P3^3;


u8 i = 0, xdata tmp; 
static u8 xdata count = 0;
static char xdata time_now[7];
static char time_ascii[14];

//functions prototype:
static void print_time();
void delay_50ms();


void main()
{
	EA = 0;
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
				// update display
				EA = 0; // Disable Interrupt
				lcd1602_show_str(6,1, "  ", 2);  // modify here (x,y)          2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII.
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII.
				lcd1602_show_str(6,1, &time_ascii[2*count-2], 2); // modify here (x,y)         3
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			case 2:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 59) tmp = 0;	//modify here         1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				// update display
				EA = 0; // Disable Interrupt
				lcd1602_show_str(3,1, "  ", 2);  // modify here (x,y)           2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII.
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII.
				lcd1602_show_str(3,1, &time_ascii[2*count-2], 2); // modify here (x,y)          3
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			case 3:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 23) tmp = 0;	//modify here          1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				// update display
				EA = 0; // Disable Interrupt
				lcd1602_show_str(0,1, "  ", 2);  // modify here (x,y)          2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII.
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII.
				lcd1602_show_str(0,1, &time_ascii[2*count-2], 2); // modify here (x,y)           3
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			case 4:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 7) tmp = 1;	//modify here             1 
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				// update display
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
				// update display
				EA = 0; // Disable Interrupt
				lcd1602_show_str(8,0, "  ", 2);  // modify here (x,y)             2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII.
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII.
				lcd1602_show_str(8,0, &time_ascii[2*count-2], 2); // modify here (x,y)       3
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			case 6:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 12) tmp = 1;	//modify here            1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				// update display
				EA = 0; // Disable Interrupt
				lcd1602_show_str(5,0, "  ", 2);  // modify here (x,y)            2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII.
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII.
				lcd1602_show_str(5,0, &time_ascii[2*count-2], 2); // modify here (x,y)       3
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			case 7:
				tmp = BCD_TO_BIN(time_now[count-1]);
				if (KEY1 == 0) {
					tmp++;
					if (tmp > 99) tmp = 0;     // modify here         1
					time_now[count-1] = BIN_TO_BCD(tmp);
				}
				// update display
				EA = 0; // Disable Interrupt
				lcd1602_show_str(2,0, "  ", 2); // modify here (x,y)             2
				for(i=2; i > 0; i--) delay_50ms();
				time_ascii[2*count-1] = time_now[count-1] & 63 | 48;    // BCD TO ASCII
				time_ascii[2*count-2] = time_now[count-1] >>4 &63 | 48; // BCD TO ASCII
				lcd1602_show_str(2,0, &time_ascii[2*count-2], 2); // modify here (x,y)        3
				EA = 1;		//Enable Interrupt
				for(i=2; i > 0; i--) delay_50ms();
				break;
			default:
				lcd1602_show_str(11,0, "error", 5);
				break;
			}
		}
		ds1302_set_time(time_now);
	}
	
}


static void print_time()
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
	if (KEY0 == 0) {
		if(!count)
			count = 7;
		else 
			count--;

		for(i=11; i > 0; i--)
			delay_50ms();
	}
}


