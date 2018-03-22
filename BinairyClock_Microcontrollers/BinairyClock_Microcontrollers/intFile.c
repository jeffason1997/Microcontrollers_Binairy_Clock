/*
 * intFile.c
 *
 * Created: 22-3-2018 13:50:12
 *  Author: jeffr
 */ 

 #include <time.h>
 #include "headerFiles/intFile.h"

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