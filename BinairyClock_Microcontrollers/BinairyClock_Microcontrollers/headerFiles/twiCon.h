/*
 * twiCon.h
 *
 * Created: 22-3-2018 14:02:40
 *  Author: jeffr
 */ 
  #define u_char unsigned char
  #define BCD2BIN(x) ((((u_char)(x)) >> 4) * 10 + ((x) & 0x0F))
  #define BIN2BCD(x) (((((u_char)(x)) / 10) << 4) + (x) % 10)

void twi_init(void);
void twi_start(void);
void twi_stop(void);
void twi_tx(unsigned char data);
void twi_rx(unsigned char data);