//*****************************************************************************
// STE2007.c - This file provide some basic interface with STE2007 GLCD driver
// for MSP430 and ARM M4F from Texas Instrument. Software SPI is used instead
// of hardware SPI, so you can use this code for any microcontroller with just
// only a few adjustments.
//
// Copyright (c) Ho Tuan Vu, aka HTV, golden.spirit92@gmail.com
//
// To use these function, you must copy this file to your project and include
// the header file STE2007.h in the main.c file
// You must also configure some parameters in the USER CONFIGURATION SECTION
// in the STE2007.h file.
//
// This project contains ABSOLUTELY NO WARRANTY, meaning it does not even have
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  If there's a bug in this code that smokes your board, sorry, but
// you're on your own.
//*****************************************************************************
// IMPORT
//*****************************************************************************
#include <stdint.h>
#include <stdbool.h>
#include "STE2007.h"
#include "stdarg.h"

#ifdef	PIN_CONFIG_MSP430
#include <msp430.h>
#endif

#ifdef	PIN_CONFIG_ARM
#include "../include.h"
#endif
static const char * const g_pcHex = "0123456789abcdef";

//*****************************************************************************
// ASCII table
//*****************************************************************************
const char ASCII[][6] ={
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // 20
		,{0x00, 0x00, 0x00, 0x5f, 0x00, 0x00} // 21 !
		,{0x00, 0x00, 0x07, 0x00, 0x07, 0x00} // 22 "
		,{0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14} // 23 #
		,{0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12} // 24 $
		,{0x00, 0x23, 0x13, 0x08, 0x64, 0x62} // 25 %
		,{0x00, 0x36, 0x49, 0x55, 0x22, 0x50} // 26 &
		,{0x00, 0x00, 0x05, 0x03, 0x00, 0x00} // 27 '
		,{0x00, 0x00, 0x1c, 0x22, 0x41, 0x00} // 28 (
		,{0x00, 0x00, 0x41, 0x22, 0x1c, 0x00} // 29 )
		,{0x00, 0x14, 0x08, 0x3e, 0x08, 0x14} // 2a *
		,{0x00, 0x08, 0x08, 0x3e, 0x08, 0x08} // 2b +
		,{0x00, 0x00, 0x50, 0x30, 0x00, 0x00} // 2c ,
		,{0x00, 0x08, 0x08, 0x08, 0x08, 0x08} // 2d -
		,{0x00, 0x00, 0x60, 0x60, 0x00, 0x00} // 2e .
		,{0x00, 0x20, 0x10, 0x08, 0x04, 0x02} // 2f /
		,{0x00, 0x3e, 0x51, 0x49, 0x45, 0x3e} // 30 0
		,{0x00, 0x00, 0x42, 0x7f, 0x40, 0x00} // 31 1
		,{0x00, 0x42, 0x61, 0x51, 0x49, 0x46} // 32 2
		,{0x00, 0x21, 0x41, 0x45, 0x4b, 0x31} // 33 3
		,{0x00, 0x18, 0x14, 0x12, 0x7f, 0x10} // 34 4
		,{0x00, 0x27, 0x45, 0x45, 0x45, 0x39} // 35 5
		,{0x00, 0x3c, 0x4a, 0x49, 0x49, 0x30} // 36 6
		,{0x00, 0x01, 0x71, 0x09, 0x05, 0x03} // 37 7
		,{0x00, 0x36, 0x49, 0x49, 0x49, 0x36} // 38 8
		,{0x00, 0x06, 0x49, 0x49, 0x29, 0x1e} // 39 9
		,{0x00, 0x00, 0x36, 0x36, 0x00, 0x00} // 3a :
		,{0x00, 0x00, 0x56, 0x36, 0x00, 0x00} // 3b ;
		,{0x00, 0x08, 0x14, 0x22, 0x41, 0x00} // 3c <
		,{0x00, 0x14, 0x14, 0x14, 0x14, 0x14} // 3d =
		,{0x00, 0x00, 0x41, 0x22, 0x14, 0x08} // 3e >
		,{0x00, 0x02, 0x01, 0x51, 0x09, 0x06} // 3f ?
		,{0x00, 0x32, 0x49, 0x79, 0x41, 0x3e} // 40 @
		,{0x00, 0x7e, 0x11, 0x11, 0x11, 0x7e} // 41 A
		,{0x00, 0x7f, 0x49, 0x49, 0x49, 0x36} // 42 B
		,{0x00, 0x3e, 0x41, 0x41, 0x41, 0x22} // 43 C
		,{0x00, 0x7f, 0x41, 0x41, 0x22, 0x1c} // 44 D
		,{0x00, 0x7f, 0x49, 0x49, 0x49, 0x41} // 45 E
		,{0x00, 0x7f, 0x09, 0x09, 0x09, 0x01} // 46 F
		,{0x00, 0x3e, 0x41, 0x49, 0x49, 0x7a} // 47 G
		,{0x00, 0x7f, 0x08, 0x08, 0x08, 0x7f} // 48 H
		,{0x00, 0x00, 0x41, 0x7f, 0x41, 0x00} // 49 I
		,{0x00, 0x20, 0x40, 0x41, 0x3f, 0x01} // 4a J
		,{0x00, 0x7f, 0x08, 0x14, 0x22, 0x41} // 4b K
		,{0x00, 0x7f, 0x40, 0x40, 0x40, 0x40} // 4c L
		,{0x00, 0x7f, 0x02, 0x0c, 0x02, 0x7f} // 4d M
		,{0x00, 0x7f, 0x04, 0x08, 0x10, 0x7f} // 4e N
		,{0x00, 0x3e, 0x41, 0x41, 0x41, 0x3e} // 4f O
		,{0x00, 0x7f, 0x09, 0x09, 0x09, 0x06} // 50 P
		,{0x00, 0x3e, 0x41, 0x51, 0x21, 0x5e} // 51 Q
		,{0x00, 0x7f, 0x09, 0x19, 0x29, 0x46} // 52 R
		,{0x00, 0x46, 0x49, 0x49, 0x49, 0x31} // 53 S
		,{0x00, 0x01, 0x01, 0x7f, 0x01, 0x01} // 54 T
		,{0x00, 0x3f, 0x40, 0x40, 0x40, 0x3f} // 55 U
		,{0x00, 0x1f, 0x20, 0x40, 0x20, 0x1f} // 56 V
		,{0x00, 0x3f, 0x40, 0x38, 0x40, 0x3f} // 57 W
		,{0x00, 0x63, 0x14, 0x08, 0x14, 0x63} // 58 X
		,{0x00, 0x07, 0x08, 0x70, 0x08, 0x07} // 59 Y
		,{0x00, 0x61, 0x51, 0x49, 0x45, 0x43} // 5a Z
		,{0x00, 0x00, 0x7f, 0x41, 0x41, 0x00} // 5b [
		,{0x00, 0x02, 0x04, 0x08, 0x10, 0x20} // 5c ¥
		,{0x00, 0x00, 0x41, 0x41, 0x7f, 0x00} // 5d ]
		,{0x00, 0x04, 0x02, 0x01, 0x02, 0x04} // 5e ^
		,{0x00, 0x40, 0x40, 0x40, 0x40, 0x40} // 5f _
		,{0x00, 0x00, 0x01, 0x02, 0x04, 0x00} // 60 `
		,{0x00, 0x20, 0x54, 0x54, 0x54, 0x78} // 61 a
		,{0x00, 0x7f, 0x48, 0x44, 0x44, 0x38} // 62 b
		,{0x00, 0x38, 0x44, 0x44, 0x44, 0x20} // 63 c
		,{0x00, 0x38, 0x44, 0x44, 0x48, 0x7f} // 64 d
		,{0x00, 0x38, 0x54, 0x54, 0x54, 0x18} // 65 e
		,{0x00, 0x08, 0x7e, 0x09, 0x01, 0x02} // 66 f
		,{0x00, 0x0c, 0x52, 0x52, 0x52, 0x3e} // 67 g
		,{0x00, 0x7f, 0x08, 0x04, 0x04, 0x78} // 68 h
		,{0x00, 0x00, 0x44, 0x7d, 0x40, 0x00} // 69 i
		,{0x00, 0x20, 0x40, 0x44, 0x3d, 0x00} // 6a j
		,{0x00, 0x7f, 0x10, 0x28, 0x44, 0x00} // 6b k
		,{0x00, 0x00, 0x41, 0x7f, 0x40, 0x00} // 6c l
		,{0x00, 0x7c, 0x04, 0x18, 0x04, 0x78} // 6d m
		,{0x00, 0x7c, 0x08, 0x04, 0x04, 0x78} // 6e n
		,{0x00, 0x38, 0x44, 0x44, 0x44, 0x38} // 6f o
		,{0x00, 0x7c, 0x14, 0x14, 0x14, 0x08} // 70 p
		,{0x00, 0x08, 0x14, 0x14, 0x18, 0x7c} // 71 q
		,{0x00, 0x7c, 0x08, 0x04, 0x04, 0x08} // 72 r
		,{0x00, 0x48, 0x54, 0x54, 0x54, 0x20} // 73 s
		,{0x00, 0x04, 0x3f, 0x44, 0x40, 0x20} // 74 t
		,{0x00, 0x3c, 0x40, 0x40, 0x20, 0x7c} // 75 u
		,{0x00, 0x1c, 0x20, 0x40, 0x20, 0x1c} // 76 v
		,{0x00, 0x3c, 0x40, 0x30, 0x40, 0x3c} // 77 w
		,{0x00, 0x44, 0x28, 0x10, 0x28, 0x44} // 78 x
		,{0x00, 0x0c, 0x50, 0x50, 0x50, 0x3c} // 79 y
		,{0x00, 0x44, 0x64, 0x54, 0x4c, 0x44} // 7a z
		,{0x00, 0x00, 0x08, 0x36, 0x41, 0x00} // 7b {
		,{0x00, 0x00, 0x00, 0x7f, 0x00, 0x00} // 7c |
		,{0x00, 0x00, 0x41, 0x36, 0x08, 0x00} // 7d }
		,{0x00, 0x10, 0x08, 0x08, 0x10, 0x08} // 7e ->
		,{0x00, 0x78, 0x46, 0x41, 0x46, 0x78} // 7f <-
};
//*****************************************************************************
// PUBLIC FUNCTION:
// lcd_init(void)					: Initialize LCD
// lcd_write(char dc, char byte)	: Send data or command to LCD
//									  dc = FLAG_CMD  : command
//									  dc = FLAG_DATA : data
// lcd_clear(void)					: Clear all pixels on LCD
// lcd_gotoxy(unsigned char col, unsigned char row)	: Set pointer to coordinate(column, row)
// lcd_normal(void)					: Set LCD to normal state (display on, invert off,...)
// lcd_all(void)					: Display all pixels
// lcd_putc(char c)					: Display ASCII character on LCD
// lcd_puts(char *s)				: Display character string on LCD
//*****************************************************************************
void lcd_write(CS_LCD eCS_LCD,char dc, char byte){
	char i;
	if(dc) LCD_SDA_HIGH;
	else LCD_SDA_LOW;

	switch(eCS_LCD)
	{
	case LCD_1: 	LCD_CS1_LOW;break;
	case LCD_2: 	LCD_CS2_LOW;break;
	case LCD_3: 	LCD_CS3_LOW;break;
	case LCD_ALL:
		LCD_CS1_LOW;
		LCD_CS2_LOW;
		LCD_CS3_LOW;
		break;
	}

	LCD_CLK_HIGH;
	LCD_CLK_LOW;

	// shift data out
	for(i = 0; i < 8; i++){
		if((byte<<i) & 0x80) LCD_SDA_HIGH;
		else LCD_SDA_LOW;
		LCD_CLK_HIGH;
		LCD_CLK_LOW;
	}
	switch(eCS_LCD)
	{
	case LCD_1: 	LCD_CS1_HIGH;break;
	case LCD_2: 	LCD_CS2_HIGH;break;
	case LCD_3: 	LCD_CS3_HIGH;break;
	case LCD_ALL:
		LCD_CS1_HIGH;
		LCD_CS2_HIGH;
		LCD_CS3_HIGH;
		break;
	}
}

//******************************************************************************
void lcd_init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	LCD_PIN_TYPE_OUTPUT;

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	LCD_PIN_TYPE_CS;

	ROM_SysCtlDelay(SysCtlClockGet()/1000);
	LCD_RESET_LOW;
	ROM_SysCtlDelay(SysCtlClockGet()/1000);

	LCD_CS1_HIGH;
	LCD_CS2_HIGH;
	LCD_CS3_HIGH;
	ROM_SysCtlDelay(SysCtlClockGet()/1000);

	LCD_CLK_LOW;
	ROM_SysCtlDelay(SysCtlClockGet()/1000);
	LCD_RESET_HIGH;


	ROM_SysCtlDelay(SysCtlClockGet()/1000);

	lcd_write(LCD_ALL, FLAG_CMD, 0x20);						// Set voltage range
	lcd_write(LCD_ALL, FLAG_CMD, LCD_CONTRAST);

	lcd_write(LCD_ALL, FLAG_CMD, LCD_MODE | NORMAL);
	lcd_write(LCD_ALL, FLAG_CMD, LCD_CHARGE_PUMP_ON);		// Enable charge pump
	lcd_write(LCD_ALL, FLAG_CMD, LCD_MODE | ON);			// Display on
	lcd_write(LCD_ALL, FLAG_CMD, 0x9F);

	lcd_clear(LCD_ALL);
}

//*****************************************************************************
void lcd_clear(CS_LCD eCS_LCD){
	unsigned int index;
	lcd_gotoxy(eCS_LCD, 0,0);
	for(index=0; index < 864; index++){
		lcd_write(eCS_LCD, FLAG_DATA,0x00);
	}
	lcd_gotoxy(eCS_LCD, 0,0);
}

//*****************************************************************************
void lcd_gotoxy(CS_LCD eCS_LCD, unsigned char col, unsigned char row){
	lcd_write(eCS_LCD, FLAG_CMD,LCD_CHANGE_COL_LSB | ( col & 0x0F));
	lcd_write(eCS_LCD, FLAG_CMD,LCD_CHANGE_COL_MSB | ((col >> 4) & 0x07 ));
	lcd_write(eCS_LCD, FLAG_CMD,LCD_CHANGE_ROW | (row & 0x0F));
}

//*****************************************************************************
void lcd_normal(CS_LCD eCS_LCD){
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MODE|ON);
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MODE|NON_REVERSE);
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MODE|NORMAL);
	lcd_write(eCS_LCD, FLAG_CMD,LCD_RAM_ADDR_VER_MODE);
}

//*****************************************************************************
void lcd_all(CS_LCD eCS_LCD){
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MODE|ON);
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MODE|NON_REVERSE);
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MODE|ALL);
}
//******************************************************************************
void lcd_mirror_x(CS_LCD eCS_LCD){
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MIRROR_X);
}
//******************************************************************************
void lcd_mirror_y(CS_LCD eCS_LCD){
	lcd_write(eCS_LCD, FLAG_CMD,LCD_MIRROR_Y);
}
//******************************************************************************
void lcd_putc(CS_LCD eCS_LCD, char c){
	if((c >= 0x20) && (c <= 0x7f)){
		char i;
		c -= 0x20;
		for(i = 0; i < 6; i++){
			lcd_write(eCS_LCD, FLAG_DATA, ASCII[c][i]);
		}
	}
}

//******************************************************************************
void lcd_puts(CS_LCD eCS_LCD, char *s){
	while(*s){
		lcd_putc(eCS_LCD, *s++);
	}
}
//******************************************************************************
void lcd_putn(CS_LCD eCS_LCD, unsigned long num){
	signed char i;
	char num_str[3];

	for(i = 0; i < 3; i++) num_str[i] = 0xFF;//null char

	if(num == 0) lcd_putc(eCS_LCD, '0');
	else{
		i = 2;
		while((num != 0)&&(i >= 0)){
	 	num_str[i] = (num % (10)) + 0x30;
	 	i--;
	 	num = num / 10;
		}

	lcd_puts(eCS_LCD, num_str);
	}
}
//******************************************************************************
void LCDDataWrite(CS_LCD eCS_LCD, const char *pcBuf, uint32_t ulLen){
	uint32_t i;
	for(i = 0; i < ulLen; i++){
		lcd_putc(eCS_LCD, *pcBuf);
		pcBuf++;
	}
}
//******************************************************************************
//*****************************************************************************
//
//! A simple LCD based printf function supporting \%c, \%d, \%p, \%s, \%u,
//! \%x, and \%X.
//!
//! \param pcString is the format string.
//! \param ... are the optional arguments, which depend on the contents of the
//! format string.
//!
//! This function is very similar to the C library <tt>fprintf()</tt> function.
//! All of its output will be sent to the LCD.  Only the following formatting
//! characters are supported:
//!
//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
//! - \%\% to print out a \% character
//!
//! For \%s, \%d, \%i, \%u, \%p, \%x, and \%X, an optional number may reside
//! between the \% and the format character, which specifies the minimum number
//! of characters to use for that value; if preceded by a 0 then the extra
//! characters will be filled with zeros instead of spaces.  For example,
//! ``\%8d'' will use eight characters to print the decimal value with spaces
//! added to reach eight; ``\%08d'' will use eight characters as well but will
//! add zeroes instead of spaces.
//!
//! The type of the arguments after \e pcString must match the requirements of
//! the format string.  For example, if an integer was passed where a string
//! was expected, an error of some kind will most likely occur.
//!
//! \return None.
//
//*****************************************************************************
void
LCDprintf(CS_LCD eCS_LCD, const char *pcString, ...)
{
	static unsigned int ulPos, ulCount, ulNeg;
	unsigned long ulValue, ulBase, ulIdx;
	char *pcStr, pcBuf[16], cFill;
	va_list vaArgP;

	//
	// Start the varargs processing.
	//
	va_start(vaArgP, pcString);

	//
	// Loop while there are more characters in the string.
	//
	while(*pcString)
	{
		//
		// Find the first non-% character, or the end of the string.
		//
		for(ulIdx = 0; (pcString[ulIdx] != '%') && (pcString[ulIdx] != '\0');
				ulIdx++)
		{
		}

		//
		// Write this portion of the string.
		//
		LCDDataWrite(eCS_LCD, pcString, ulIdx);

		//
		// Skip the portion of the string that was written.
		//
		pcString += ulIdx;

		//
		// See if the next character is a %.
		//
		if(*pcString == '%')
		{
			//
			// Skip the %.
			//
			pcString++;

			//
			// Set the digit count to zero, and the fill character to space
			// (i.e. to the defaults).
			//
			ulCount = 0;
			cFill = ' ';

			//
			// It may be necessary to get back here to process more characters.
			// Goto's aren't pretty, but effective.  I feel extremely dirty for
			// using not one but two of the beasts.
			//
			again:

			//
			// Determine how to handle the next character.
			//
			switch(*pcString++)
			{
			//
			// Handle the digit characters.
			//
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			{
				//
				// If this is a zero, and it is the first digit, then the
				// fill character is a zero instead of a space.
				//
				if((pcString[-1] == '0') && (ulCount == 0))
				{
					cFill = '0';
				}

				//
				// Update the digit count.
				//
				ulCount *= 10;
				ulCount += pcString[-1] - '0';

				//
				// Get the next character.
				//
				goto again;
			}

			//
			// Handle the %c command.
			//
			case 'c':
			{
				//
				// Get the value from the varargs.
				//
				ulValue = va_arg(vaArgP, unsigned long);

				//
				// Print out the character.
				//
				LCDDataWrite(eCS_LCD, (char *)&ulValue, 1);

				//
				// This command has been handled.
				//
				break;
			}

			//
			// Handle the %d and %i commands.
			//
			case 'd':
			case 'i':
			{
				//
				// Get the value from the varargs.
				//
				ulValue = va_arg(vaArgP, unsigned long);

				//
				// Reset the buffer position.
				//
				ulPos = 0;

				//
				// If the value is negative, make it positive and indicate
				// that a minus sign is needed.
				//
				if((long)ulValue < 0)
				{
					//
					// Make the value positive.
					//
					ulValue = -(long)ulValue;

					//
					// Indicate that the value is negative.
					//
					ulNeg = 1;
				}
				else
				{
					//
					// Indicate that the value is positive so that a minus
					// sign isn't inserted.
					//
					ulNeg = 0;
				}

				//
				// Set the base to 10.
				//
				ulBase = 10;

				//
				// Convert the value to ASCII.
				//
				goto convert;
			}

			//
			// Handle the %s command.
			//
			case 's':
			{
				//
				// Get the string pointer from the varargs.
				//
				pcStr = va_arg(vaArgP, char *);

				//
				// Determine the length of the string.
				//
				for(ulIdx = 0; pcStr[ulIdx] != '\0'; ulIdx++)
				{
				}

				//
				// Write the string.
				//
				LCDDataWrite(eCS_LCD, pcStr, ulIdx);

				//
				// Write any required padding spaces
				//
				if(ulCount > ulIdx)
				{
					ulCount -= ulIdx;
					while(ulCount--)
					{
						LCDDataWrite(eCS_LCD, " ", 1);
					}
				}
				//
				// This command has been handled.
				//
				break;
			}

			//
			// Handle the %u command.
			//
			case 'u':
			{
				//
				// Get the value from the varargs.
				//
				ulValue = va_arg(vaArgP, unsigned long);

				//
				// Reset the buffer position.
				//
				ulPos = 0;

				//
				// Set the base to 10.
				//
				ulBase = 10;

				//
				// Indicate that the value is positive so that a minus sign
				// isn't inserted.
				//
				ulNeg = 0;

				//
				// Convert the value to ASCII.
				//
				goto convert;
			}

			//
			// Handle the %x and %X commands.  Note that they are treated
			// identically; i.e. %X will use lower case letters for a-f
			// instead of the upper case letters is should use.  We also
			// alias %p to %x.
			//
			case 'x':
			case 'X':
			case 'p':
			{
				//
				// Get the value from the varargs.
				//
				ulValue = va_arg(vaArgP, unsigned long);

				//
				// Reset the buffer position.
				//
				ulPos = 0;

				//
				// Set the base to 16.
				//
				ulBase = 16;

				//
				// Indicate that the value is positive so that a minus sign
				// isn't inserted.
				//
				ulNeg = 0;

				//
				// Determine the number of digits in the string version of
				// the value.
				//
				convert:
				for(ulIdx = 1;
						(((ulIdx * ulBase) <= ulValue) &&
								(((ulIdx * ulBase) / ulBase) == ulIdx));
						ulIdx *= ulBase, ulCount--)
				{
				}

				//
				// If the value is negative, reduce the count of padding
				// characters needed.
				//
				if(ulNeg)
				{
					ulCount--;
				}

				//
				// If the value is negative and the value is padded with
				// zeros, then place the minus sign before the padding.
				//
				if(ulNeg && (cFill == '0'))
				{
					//
					// Place the minus sign in the output buffer.
					//
					pcBuf[ulPos++] = '-';

					//
					// The minus sign has been placed, so turn off the
					// negative flag.
					//
					ulNeg = 0;
				}

				//
				// Provide additional padding at the beginning of the
				// string conversion if needed.
				//
				if((ulCount > 1) && (ulCount < 16))
				{
					for(ulCount--; ulCount; ulCount--)
					{
						pcBuf[ulPos++] = cFill;
					}
				}

				//
				// If the value is negative, then place the minus sign
				// before the number.
				//
				if(ulNeg)
				{
					//
					// Place the minus sign in the output buffer.
					//
					pcBuf[ulPos++] = '-';
				}

				//
				// Convert the value into a string.
				//
				for(; ulIdx; ulIdx /= ulBase)
				{
					pcBuf[ulPos++] = g_pcHex[(ulValue / ulIdx) % ulBase];
				}

				//
				// Write the string.
				//
				LCDDataWrite(eCS_LCD, pcBuf, ulPos);

				//
				// This command has been handled.
				//
				break;
			}

			//
			// Handle the %% command.
			//
			case '%':
			{
				//
				// Simply write a single %.
				//
				LCDDataWrite(eCS_LCD, pcString - 1, 1);

				//
				// This command has been handled.
				//
				break;
			}

			//
			// Handle all other commands.
			//
			default:
			{
				//
				// Indicate an error.
				//
				LCDDataWrite(eCS_LCD, "ERROR", 5);

				//
				// This command has been handled.
				//
				break;
			}
			}
		}
	}

	//
	// End the varargs processing.
	//
	va_end(vaArgP);
}

