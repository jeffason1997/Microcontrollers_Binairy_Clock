/*
 * RTC.c
 *
 * Created: 22-3-2018 13:55:13
 *  Author: jeffr
 */ 

 #include "headerFiles/RTC.h"
 #include "headerFiles/twiCon.h"

 void setupTime(struct tm *timeinf){
 	twi_start();
 	twi_tx(0b11010000);					// Display I2C address + R/W bit RTC
 	twi_tx(0b00000010);					// word address RTC
 	twi_tx(BCD2BIN(timeinf->tm_sec));	// write data seconds
 	twi_tx(BCD2BIN(timeinf->tm_min));	// write data minutes
 	twi_tx(BCD2BIN(timeinf->tm_hour));	// write data hours
 	twi_stop();
}

 void updateTime(struct tm *timeinf2){
	 twi_start();
	 twi_tx(0b11010001);					// Display I2C addres + R/W bit
	 twi_tx(0b00000010);					// word address RTC
	 twi_tx(BIN2BCD(timeinf2->tm_sec));	// read seconds RTC
	 twi_tx(BIN2BCD(timeinf2->tm_min));
	 twi_tx(BIN2BCD(timeinf2->tm_hour));
	 twi_stop();
 }