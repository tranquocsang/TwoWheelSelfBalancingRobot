#ifndef PCF8814_H_
#define PCF8814_H_
//*****************************************************************************

//*****************************************************************************
//*****************************************************************************
// USER CONFIGURATION SECTION
//*****************************************************************************
// The following parameters need to be configured by the user.

#define PIN_CONFIG_ARM					// For using ARM M4, define PIN_CONFIG_ARM
//#define PIN_CONFIG_MSP430  					// For using MSP430, define PIN_CONFIG_MSP430

#define LCD_CONTRAST 		(0x9F)			// Value range should be 0x80 -> 0x9F

//*****************************************************************************
// Define some basic commands.
//*****************************************************************************
// To change the hardware connection, simply replace the correspondent Port
// and Bit
#ifdef PIN_CONFIG_MSP430					// Pin configuration for msp430

#define LCD_PIN_TYPE_OUTPUT	P2DIR |= BIT0 + BIT1 + BIT2 + BIT3

#define LCD_CS_LOW			P2OUT &= ~BIT1
#define LCD_CS_HIGH			P2OUT |= BIT1

#define LCD_RESET_LOW		P2OUT &= ~BIT0
#define LCD_RESET_HIGH		P2OUT |= BIT0

#define LCD_SDA_HIGH		P2OUT |= BIT2
#define LCD_SDA_LOW			P2OUT &= ~BIT2

#define LCD_CLK_HIGH		P2OUT |= BIT3
#define LCD_CLK_LOW			P2OUT &= ~BIT3
#endif

//*****************************************************************************
#ifdef PIN_CONFIG_ARM					// Pin configuration for ARM M4

#define LCD_PIN_TYPE_OUTPUT	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)
#define LCD_PIN_TYPE_CS		GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_4 | GPIO_PIN_6 | GPIO_PIN_7)

#define LCD_CS1_LOW			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0x00)
#define LCD_CS1_HIGH		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4, 0xFF)

#define LCD_CS2_LOW			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0x00)
#define LCD_CS2_HIGH		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_7, 0xFF)

#define LCD_CS3_LOW			GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0x00)
#define LCD_CS3_HIGH		GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_6, 0xFF)

#define LCD_RESET_LOW		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0x00)
#define LCD_RESET_HIGH		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0xFF)

#define LCD_SDA_HIGH		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0xFF)
#define LCD_SDA_LOW			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0x00)

#define LCD_CLK_HIGH		GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0xFF)
#define LCD_CLK_LOW			GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0x00)
#endif

typedef enum
{
	LCD_1 = 1,
	LCD_2 = 2,
	LCD_3 = 3,
	LCD_ALL = 4
}CS_LCD;

//******************************************************************************
// END OF USER CONFIGURATION SECTION
//******************************************************************************
//******************************************************************************
//******************************************************************************

//******************************************************************************
// Public function header
//******************************************************************************
void lcd_write(CS_LCD eCS_LCD, char dc, char byte);
void lcd_init(void);
void lcd_clear(CS_LCD eCS_LCD);
void lcd_gotoxy(CS_LCD eCS_LCD, unsigned char col, unsigned char row);
void lcd_normal(CS_LCD eCS_LCD);
void lcd_all(CS_LCD eCS_LCD);
void lcd_putc(CS_LCD eCS_LCD, char c);
void lcd_puts(CS_LCD eCS_LCD, char *s);
void lcd_putn(CS_LCD eCS_LCD, unsigned long num);
void LCDprintf(CS_LCD eCS_LCD, const char *pcString, ...);
//*****************************************************************************
// COMMAND LIST
//*****************************************************************************
#define LCD_RESET_CYCLES		(CPU_CLOCK_MHZ*200)

#define FLAG_CMD				(0x00)
#define FLAG_DATA				(0x01)

// Display mode
#define ON						(0x0F)			// Display on
#define OFF						(0x0E)			// Display off
#define ALL						(0x05)			// All points ON
#define NORMAL					(0x04)			// Normal display
#define NON_REVERSE				(0x06)			// Non-reverse display
#define REVERSE					(0x07)			// Reverse display

#define LCD_MODE 				(0xA0)			// Display mode command identifier

#define LCD_NOP 				(0xE3)
#define LCD_CHARGE_PUMP_ON		(0x2F)
#define LCD_RAM_ADDR_VER_MODE	(0xAB)
#define LCD_RAM_ADDR_HOR_MODE	(0xAA)
#define LCD_CHANGE_COL_LSB 		(0x00)
#define LCD_CHANGE_COL_MSB		(0x10)
#define LCD_CHANGE_ROW 			(0xB0)
#define LCD_MIRROR_Y			(0xC8)
#define LCD_MIRROR_X 			(0xA1)
#define LCD_EXT_OSC 			(0x3A)
#define LCD_SOFT_RESET 			(0xE2)

#endif /* PCF8814_H_ */
