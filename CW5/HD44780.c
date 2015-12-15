#include "HD44780.h"



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
	WriteByte(text);
};

void LCD_GoToXY(unsigned char x, unsigned char y)
{
	
};

void LCD_Clear()
{
	LCD_Command(1);
};

void LCD_Home()
{
	LCD_Command(2);
};

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
	
	LCD_Command(0x04);
	_delay_ms(1);
	
	LCD_Command(0x0f);
	_delay_ms(1);
};