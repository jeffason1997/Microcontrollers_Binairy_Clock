/* ---------------------------------------------------------------------------
** Author: 			jlanting@avans.nl
** -------------------------------------------------------------------------*/

#define F_CPU 8000000
#define MAXPLACES 8

#include <util/delay.h>
#include <time.h>
#include "headerFiles/intFile.h"
#include "headerFiles/RTC.h"
#include "headerFiles/twiCon.h"

struct tm timeinf;		//time struct for time setup
struct tm timeinf2;		//time struct for reading RTC
unsigned char horizontalAdress[MAXPLACES]={ 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E};	//all lines on the board

void wait( int ms ) {
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
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

	setupTime(&timeinf);
	
	while (1)
	{
		int j;
		updateTime(&timeinf2);

		//--------------------------------------------------------------------
		for(j=0;j!=MAXPLACES;j++){		//for all places on the board		|
			twi_start();				//									|
			twi_tx(0b11100000);	// Display I2C address + R/W bit			|
			twi_tx(horizontalAdress[j]);	// Address						|		out commend this section to see if RTC works
			twi_tx(getTimeInt(j,&timeinf));	// data							|
			twi_stop();						//								|
		}									//								|
		//-------------------------------------------------------------------
		
		wait(1000);	// wait for a second
	
				
		for(j=0;j!=MAXPLACES;j++){		//for all places on the board
			twi_start();
			twi_tx(0b11100000);	// Display I2C address + R/W bit
			twi_tx(horizontalAdress[j]);	// Address
			twi_tx(getTimeInt(j,&timeinf2));	// data
			twi_stop();
		}
	}

	return 1;
}
