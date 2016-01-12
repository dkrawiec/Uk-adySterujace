#include "HD44780.h"
#include "hd44780-charmap.h"

void WriteNibble(unsigned char nibbleToWrite)
{
	LCD_PORT |= 1<<EN;
	LCD_PORT = (LCD_PORT & 0xf0) | (nibbleToWrite & 0x0f);
	LCD_PORT &= ~(1<<EN);
}


void WriteByte(unsigned char dataToWrite)
{
	WriteNibble(dataToWrite >> 4);
	WriteNibble(dataToWrite & 0x0f);
}


void LCD_Command(unsigned char cmd)
{
	LCD_PORT &= ~(1<<RS);
	WriteByte(cmd);
};

void LCD_Text(char * text)
{
	LCD_PORT |= 1<<RS;
	while (*text)
	{
		WriteByte(*text++);
		_delay_ms(100);	
	}
};

void LCD_GoToXY(unsigned char x, unsigned char y)
{
	uint8_t adr = y*(0x40)+x;
	LCD_Command(adr | (1<<7));
	_delay_ms(1);
};

void LCD_Clear()
{
	LCD_Command(1);
	_delay_ms(2);
};

void LCD_Home()
{
	LCD_Command(2);
	_delay_ms(2);
};

void start_shifting()
{
	LCD_Command(0x07);
	_delay_ms(1);
}

void stop_shifting()
{
	LCD_Command(0x06);
	_delay_ms(1);
}

void LCD_Initalize()
{
	_delay_ms(50);
	int i;
	for(i=0;i<3;i++)
	{
		WriteNibble(0x03);
		_delay_ms(5);
	}
	_delay_ms(5);
	
	WriteNibble(0x02); //set data size
	_delay_ms(0x02);
	
	LCD_Command(0x28);  //display settings
	_delay_ms(2);
	
	LCD_Command(0x08);
	_delay_ms(2);
	
	LCD_Command(0x01);
	_delay_ms(3);
	
	stop_shifting();
	
	LCD_Command(0x0f);
	_delay_ms(1);
};