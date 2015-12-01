/*
 * CW3.c
 *
 * Created: 2015-11-25 16:16:31
 *  Author: Administrator
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned int digits[10] = {
	~(1+2+4+8+16+32),		//0
	~(2+4),					//1
	~(1+2+8+16+64),			//2
	~(1+2+4+8+64),			//3
	~(2+4+32+64),			//4
	~(1+4+8+32+64),			//5
	~(1+4+8+16+32+64),		//6
	~(1+2+4),				//7
	~(1+2+4+8+16+32+64),	//8
	~(1+2+4+8+32+64)};		//9

int power(int a, unsigned int b)
{
	int result=1;
	int i;
	for(i=0;i<b;i++)
	{
		result*=a;
	}
	return result;
}

unsigned int calculateDigit(int a, unsigned n)
{
	int i;
	int number=a;
	for(i=n;i>1;i--)
	{
		number/=10;
	}
	return number%10;
}

int main(void)
{
	DDRA = 0xff;
	DDRB = 0xff;
	PORTA = digits[0];
	PORTB = ~1;

	int number=0;
	while(1)
	{
		int timer;
		for(timer=0;timer<900;timer++)
		{
			int column;

			for(column=3;column>=0;column--)
			{
				int col = power(2,column);
				PORTB = ~col;
				PORTA = digits[calculateDigit(number,3-column+1)];
				_delay_ms(1);
			}

		}
		number++;
	}
}
