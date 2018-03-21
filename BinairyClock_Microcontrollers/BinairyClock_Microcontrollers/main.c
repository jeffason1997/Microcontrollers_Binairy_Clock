/* ---------------------------------------------------------------------------
** Author: 			jlanting@avans.nl
** -------------------------------------------------------------------------*/

#define F_CPU 8000000
#define MAXPLACES 8

#include <avr/io.h>
#include <util/delay.h>
#include <time.h>

struct tm timeinf;		//time struct
unsigned char horizontalAdress[MAXPLACES]={ 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};	//all lines on the board

void twi_init(void) {
	TWSR = 0;
	TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
}

void twi_start(void) {

	TWCR = (0b10100100);
	while(0x00 == (TWCR & 0x80));
}

void twi_stop(void) {
	TWCR = (0b10010100);
}

void twi_tx(unsigned char data) {
	TWDR = data;
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
}

void wait( int ms ) {
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

int getInt(int i) {			//since the chip sees 10011000 as 00110001 this method fixes that
	int j;
	if(i%2==1)		//checks if bit 0 should active
	{
		j = i>>1;	//bitshifts 1 to the right
		j+=128;		//makes sure bit 0 is activated
	} else {
		j = i>>1;	//bitshifts 1 to the right
	}
	return j;
}

int getTimeInt(int i,struct tm* timeinfo) {			//gets the right int on the right position 
	int cTime = 0;
	int gTime = 0;


	switch(i){										// int i is the position
		case 0:										// first digit of hour
			cTime = (timeinfo->tm_hour) / 10;
			gTime = getInt(cTime);
			return gTime;

		case 1:										// second digit of hour
			cTime = (timeinfo->tm_hour) % 10;
			gTime = getInt(cTime);
			return gTime;

		case 2:										// space between hour and minutes
		
			return gTime;

		case 3:										// first digit of minutes
			cTime = (timeinfo->tm_min) / 10;
			gTime = getInt(cTime);
			return gTime;

		case 4:										// second digit of minutes
			cTime = timeinfo->tm_min % 10;
			gTime = getInt(cTime);
			return gTime;

		case 5:										// space between minutes and seconds
			
			return gTime;

		case 6:										// first digit of seconds
			cTime = timeinfo->tm_sec / 10;
			gTime = getInt(cTime);
			return gTime;

		case 7:										// second digit of seconds
			cTime = timeinfo->tm_sec % 10;
			gTime = getInt(cTime);
			return gTime;
	}
	return gTime;
}

void addTime(struct tm* date){
	date->tm_sec ++;
	if(date->tm_sec == 60){
		date->tm_sec = 0;
		date->tm_min ++;
		if(date->tm_min == 60){
			date->tm_min = 0;
			date->tm_hour ++;
			if(date->tm_hour == 24){
				date->tm_hour = 0;
			}
		}
	}
}

int main( void ) {
	//have to hardcode a time since internet connection for localtime is not available
	timeinf.tm_hour = 12;
	timeinf.tm_min = 35;
	timeinf.tm_sec = 46;
	
	twi_init();			// Init TWI interface

	// Init HT16K22. Page 32 datasheet
	twi_start();
	twi_tx(0b11100000);	// Display I2C addres + R/W bit
	twi_tx(0b00100001);	// Internal osc on (page 10 HT16K33)
	twi_stop();

	twi_start();
	twi_tx(0b11100000);	// Display I2C address + R/W bit
	twi_tx(0b10100000);	// HT16K33 pins all output
	twi_stop();

	twi_start();
	twi_tx(0b11100000);	// Display I2C address + R/W bit
	twi_tx(0b11100011);	// Display Dimming 4/16 duty cycle
	twi_stop();

	twi_start();
	twi_tx(0b11100000);	// Display I2C address + R/W bit
	twi_tx(0b10000001);	// Display ON - Blink OFF
	twi_stop();

	
	
	while (1)
	{
		int j;
		for(j=0;j!=MAXPLACES;j++){		//for all places on the board
			twi_start();
			twi_tx(0b11100000);	// Display I2C addres + R/W bit
			twi_tx(horizontalAdress[j]);	// Address
			twi_tx(getTimeInt(j,&timeinf));	// data
			twi_stop();
		}
		wait(1000);				// wait for a second
		addTime(&timeinf);		// adds second to time since hardcoded time

	}

	return 1;
}

