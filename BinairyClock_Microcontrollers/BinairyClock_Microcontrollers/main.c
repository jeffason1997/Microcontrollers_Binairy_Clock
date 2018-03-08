/*
 * BinairyClock_Microcontrollers.c
 *
 * Created: 8-3-2018 14:37:26
 * Author : jeffr
 */ 

#include <avr/io.h>
#include <time.h>

#define F_CPU 8000000


int main(void)
{

	time_t rawtime;
	struct tm * timeinfo;

    while (1) 
    {
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		
    }
}

