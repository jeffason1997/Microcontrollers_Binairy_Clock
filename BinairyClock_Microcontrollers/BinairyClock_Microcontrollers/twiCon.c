/*
 * twiCon.c
 *
 * Created: 22-3-2018 14:02:54
 *  Author: jeffr
 */ 
 #include <avr/io.h>
 #include "headerFiles/twiCon.h"

 void twi_init() {
	 TWSR = 0;
	 TWBR = 32;	 // TWI clock set to 100kHz, prescaler = 0
 }

 void twi_start() {

	 TWCR = (0b10100100);
	 while(0x00 == (TWCR & 0x80));
 }

 void twi_stop() {
	 TWCR = (0b10010100);
 }

 void twi_tx(unsigned char data) {
	 TWDR = data;
	 TWCR = (0x80 | 0x04);
	 while( 0 == (TWCR & 0x80) );
 }

 void twi_rx(unsigned char data){
	data = BIN2BCD(TWDR);
	TWCR = (0x80 | 0x04);
	while( 0 == (TWCR & 0x80) );
 }