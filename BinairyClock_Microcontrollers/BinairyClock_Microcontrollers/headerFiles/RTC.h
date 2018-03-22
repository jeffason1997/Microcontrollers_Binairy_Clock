/*
 * RTC.h
 *
 * Created: 22-3-2018 13:57:44
 *  Author: jeffr
 */ 
 #define u_char unsigned char
 #define BCD2BIN(x) ((((u_char)(x)) >> 4) * 10 + ((x) & 0x0F))
 #define BIN2BCD(x) (((((u_char)(x)) / 10) << 4) + (x) % 10)

 #include <time.h>

 void setupTime(struct tm *timeinf);
 void updateTime(struct tm *timeinf2);