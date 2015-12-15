/*
 * CW5.c
 *
 * Created: 2015-12-09 16:16:19
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include "HD44780.h"

int main(void)
{
	DDRB = 0xff;
	LCD_Initalize();
    while(1)
    {
        //TODO:: Please write your application code 
    }
}