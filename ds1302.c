#include <ds1302.h>

sbit SCLK = P1^0;
sbit IO = P1^1;
sbit RST = P1^2;


u8 code DS1302_READ_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d}; //0-7:  s,min,hours,date,month,day,year
u8 code DS1302_WRITE_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};//0-7:  s,min,hours,date,month,day,year

// Internal functionsd definitions:
static u8 ds1302_read_reg(u8 addr);
static void ds1302_write_reg(u8 addr, u8 dat);






/** External Interface definitions starts  **/

void ds1302_read_time(u8 temp[7])
{
	u8 i = 7;
	while(i--)
		temp[i] = ds1302_read_reg(DS1302_READ_ADDR[i]);
}


void ds1302_set_time(u8 time[7])
{
	u8 i = 7;
	ds1302_write_reg(0x8E,0x00);  //Disable WP and be ready to write
	while(i--)
		ds1302_write_reg(DS1302_WRITE_ADDR[i], time[i]);
	ds1302_write_reg(0x8e, 0x80); //Enable WP to disable write access
}

/** External Interface definitions end  **/







/** Internal Interface functions below:  **/

static u8 ds1302_read_reg(u8 addr)
{
	u8 i = 0, dat = 0, dat1 = 0;

	RST = 0;
	_nop_();

	SCLK = 0;
	_nop_();

	RST = 1;							// Pull-up to get ready to write
	_nop_();

	for (i=0; i<8; i++)				// send 8bit addr
	{
		IO = addr & 0x01;			// send from LSB
		addr >>= 1;

		SCLK = 1;					// Pull-up and ds1302 read 'bit
		_nop_();

		SCLK = 0;					// Pull-down for next action
		_nop_();
	}
	
	for (i=0; i<8; i++)				// read 8bit
	{
		dat1 = IO;//read start from LSB
		dat = (dat>>1) | (dat1<<7);
		SCLK = 1;
		_nop_();
		SCLK = 0;
		_nop_();
	}

	RST = 0;
	_nop_();	//Below: neccessary to stabilise ds1302

	SCLK = 1;
	_nop_();

	IO = 0;
	_nop_();

	IO = 1;
	_nop_();

	return dat;	
}


static void ds1302_write_reg(u8 addr, u8 dat)
{
	u8 i = 0;

	RST = 0;
	_nop_();				

	SCLK = 0;				
	_nop_();

	RST = 1; 				
	_nop_();

	for (i=0; i<8; i++)		//write addr
	{
		IO = addr & 0x01;	
		addr >>= 1;			
		SCLK = 1;			// Inform ds1302 to read 'bit
		_nop_();			

		SCLK = 0;	
		_nop_();
	}

	for (i=0; i<8; i++)		// Write dat to 'register
	{
		IO = dat & 0x01;
		dat >>= 1;
		SCLK = 1;	
		_nop_();
		SCLK = 0;
		_nop_();	
	}
		 
	RST = 0;					// Disable write access
	_nop_();
}



