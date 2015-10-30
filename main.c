#include "include.h"


/*
 * main.c
 */
extern int32_t accaxisX,accaxisY,accaxisZ;
extern int32_t gyroaxisX,gyroaxisY,gyroaxisZ;
void main(void)
{
	Config_System();
	UART0_init();
	initI2C();
	SysCtlDelay(SysCtlClockGet()/30);
	initMPU6050();
	SysCtlDelay(SysCtlClockGet()/30);
	IntMasterEnable(); 			//enable processor interrupts


	UARTPuts(UART0_BASE,"Test MPU6050");
	UARTPuts(UART0_BASE,"\n");
	while(1)
	{
		getMPU6050Data();
		UARTPutn(UART0_BASE,accaxisX);
		UARTPuts(UART0_BASE,"\n");
		SysCtlDelay(SysCtlClockGet()/60);
	}
}

//*****************************************************************************
//
//! Uart0 interrupt
//
//*****************************************************************************
void UART0IntHandler(void)
{
}
