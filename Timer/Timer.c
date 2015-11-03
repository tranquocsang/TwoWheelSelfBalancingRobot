/*
 * Timer.c
 *
 *  Created on: Nov 2, 2015
 *      Author: Bach
 */
#include "../include.h"
#include "Timer.h"

extern uint32_t Counter_Togle_Led;
extern bool PID_Process_Flag;
/****************************************************************
 *-----------------void Timer0Int(void)-------------------------
 * Description	: Configure Timer0A interrupt every 0.2s
 * Parameters	: none
 * Return		: don't care
 */
void Timer0Init(void)
{
	uint32_t ui32PeriodTM0;

	ROM_SysCtlPeripheralEnable(TIMER0_PERIPHERAL);							// Enable Timer1
	ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);					// Configure Timer1 is Periodic
	ui32PeriodTM0 = SysCtlClockGet()/TIMER0A_FRQ;								// Set Period of Timer1 = SysClock/10
	ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ui32PeriodTM0);				// Use TimerA of Timer1

	TimerIntRegister(TIMER0_BASE, TIMER_A, &TIMER0_ISR);

	ROM_IntEnable(INT_TIMER0A);												// Enable Timer0A interrupt
	ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	ROM_TimerControlStall(TIMER0_BASE, TIMER_A, false);
	ROM_TimerEnable(TIMER0_BASE, TIMER_A);
}
/************************************************************************
 *---------------void Timer0IntHandler(void)----------------------------
 *
 * Description	: Timer 0 interrupts handler .
 * Parameters	: none
 * Return		: don't care
 */
void TIMER0_ISR(void)
{
	ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

	PID_Process_Flag = true;
	Counter_Togle_Led++;
}
/******************************************************************************
 * ----------------void Timer1Init(void) --------------------------------------
 *
 * Description	: Timer1A interrupt 0.1s for generate PWM
 * Parameters	: none
 * Return		: don't care
 */
void Timer1Init(void)
{
	uint32_t ui32PeriodTM1;

	ROM_SysCtlPeripheralEnable(TIMER1_PERIPHERAL);							// Enable Timer1
	ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);					// Configure Timer1 is Periodic
	ui32PeriodTM1 = SysCtlClockGet()/TIMER1A_FRQ;								// Set Period of Timer1 = SysClock/10
	ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, ui32PeriodTM1);				// Use TimerA of Timer1

	TimerIntRegister(TIMER1_BASE, TIMER_A, &TIMER1_ISR);

	ROM_IntEnable(INT_TIMER1A);												// Enable Timer0A interrupt
	ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	ROM_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	ROM_TimerControlStall(TIMER1_BASE, TIMER_A, false);
	ROM_TimerEnable(TIMER1_BASE, TIMER_A);
}
/******************************************************************************
 * ------------void Timer1IntHandler(void) ------------------------------------
 *
 * Description	:
 * Parameters	: none
 * Return		: don't care
 */
void TIMER1_ISR(void)
{
	ROM_TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

	PID_Process_Flag = true;
	Counter_Togle_Led++;
}
