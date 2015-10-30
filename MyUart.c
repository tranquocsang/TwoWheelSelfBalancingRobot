/*
 * MyUart.c
 *
 *  Created on: Jul 22, 2015
 *      Author: Bach
 */

//*****************************************************************************

#include "include.h"


extern void UART0IntHandler(void);
//extern void UART1IntHandler(void);
//extern void UART2IntHandler(void);
//*****************************************************************************
//============================================================================================================
void UART0_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0); //Enable UART Peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); //Enable Port A Peripheral

	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);
	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1); //PA0 - U0RX, PA1 = U0TX

	//Configure UART; Baud Rate Set to 115200, WLEN (Word length/No. of Data Bits) set to 8, One Stop Bits, Parity None
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//IntMasterEnable(); 			//enable processor interrupts
	IntEnable(INT_UART0);		//enable the UART interrupt
	UARTIntEnable(UART0_BASE, UART_INT_RX| UART_INT_RT); //only enable RX and TX interrupts
	UARTFIFOEnable(UART0_BASE); // UART FIFO Buffer Enable
	UARTEnable(UART0_BASE);     //Enable UART

}
//============================================================================================================
void UART1_init()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1); //Enable UART Peripheral
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB); //Enable Port A Peripheral

	GPIOPinConfigure(GPIO_PB0_U1RX);
	GPIOPinConfigure(GPIO_PB1_U1TX);
	GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1); //PA0 - U0RX, PA1 = U0TX

	//Configure UART; Baud Rate Set to 115200, WLEN (Word length/No. of Data Bits) set to 8, One Stop Bits, Parity None
	UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	//IntMasterEnable(); 			//enable processor interrupts
	IntEnable(INT_UART1);		//enable the UART interrupt
	UARTIntEnable(UART1_BASE, UART_INT_RX| UART_INT_RT); //only enable RX and TX interrupts
	UARTFIFOEnable(UART1_BASE); // UART FIFO Buffer Enable
	UARTEnable(UART1_BASE);     //Enable UART

}
//*****************************************************************************
//
//! Print a string to Uart
//!
//!
//! \param UART_Base.
//! \param *s name of string.
//!
//! \return None
//
//*****************************************************************************
void UARTPuts(uint32_t UART_Base, const char *s)
{
	while(*s)
	{
		UARTCharPut(UART_Base, *s++);
	}
}
//*****************************************************************************
//
//! Print a number to Uart
//!
//!
//! \param UART_Base.
//! \param Num number you want to print.
//!
//! \return None
//
//*****************************************************************************
void UARTPutn(uint32_t UART_Base, long Num)
{
	unsigned long temp = 1;
	long NumTemp;
	NumTemp = Num;
	if (Num == 0)
	{
		UARTCharPut(UART_Base, 48);
	}
	else
	{
		if (Num < 0)
		{
			UARTCharPut(UART_Base, '-');
			Num *= -1;
		}
		while (NumTemp)
		{
			NumTemp /= 10;
			temp *= 10;
		}
		temp /= 10;
		while (temp)
		{
			UARTCharPut(UART_Base,(Num / temp) % 10 + 48);
			temp /= 10;
		}
	}
}



