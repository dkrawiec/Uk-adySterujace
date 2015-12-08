#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
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

int bilog(int a)
{
	int result = 0;
	int number = a;
	while(number>1)
	{
		number/=2;
		result++;
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

unsigned long int counter=0;	
int number = 0;
ISR(TIMER0_COMP_vect)
{
	int column = counter % 4;

	
	if((counter % 20)==0 )
	{
		DDRC = 0xf0;
		PORTC = 0x0f;
		_delay_us(10);
		uint8_t k = ~((PINC & (0x0f))|(0xf0));

		if(k!=0)
		{
			DDRC = 0x0f;
			PORTC = 0xf0;
			_delay_us(10);
			uint8_t w = ~((PINC & (0xf0))|(0x0f));

			int wiersz = 3-bilog(w>>4);
			int kolumna = 4-bilog(k);
			
			number = wiersz*4 + kolumna;	
		}
		else
		{
			
			number = 0;
		}
	}

	int col = power(2,column);
	PORTB = ~col;
	PORTA = digits[calculateDigit(number,3-column+1)];

	counter++;
}


int main(void)
{
	OCR0 = 250;
	TCCR0 |= (1 << CS01) | (1 << CS00) | (1 << WGM01);
	TIMSK |= (1<<OCIE0);
	sei();
	
	DDRA = 0xff;
	DDRB = 0xff;
	DDRC = 0x00;
	PORTB = ~0;
	
	while(1) { }
}