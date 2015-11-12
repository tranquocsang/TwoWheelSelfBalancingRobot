/*
 * MyServo.c
 *
 *  Created on: Jul 20, 2015
 *      Author: Bach
 */

#include "include.h"

uint8_t	 ui8ServoStatus;
uint8_t   ui8AdjustServo=40;
uint32_t  ui32ServoPeriod;

//*****************************************************************************
//
//! Config PWM: use for 2 motors PE4_PWM1, PE5_PWM2
//!
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void ConfigServo(void)
{
  volatile  uint32_t  ui32PWMClock;

  SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

  SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
  GPIOPinConfigure(GPIO_PD0_M1PWM0);


  ui32PWMClock = SysCtlClockGet() / 64;
  ui32ServoPeriod = (ui32PWMClock / PWM_FREQUENCY) - 1;
  PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
  PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32ServoPeriod);

  PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,  ui8AdjustServo * ui32ServoPeriod / 1000);
  PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
  PWMGenEnable(PWM1_BASE, PWM_GEN_0);
}
//*****************************************************************************
//
//! Config PWM: use for 2 motors PE4_PWM1, PE5_PWM2
//!
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void ControlServo(uint8_t ui8Adjust)
{
	if(ui8Adjust < 35) ui8Adjust=35;
	if(ui8Adjust >115) ui8Adjust=115;
    PWMGenDisable(PWM1_BASE, PWM_GEN_0);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,  ui8AdjustServo * ui32ServoPeriod / 1000);
    PWMGenEnable(PWM1_BASE, PWM_GEN_0);

}
//*****************************************************************************
//
//! Config PWM: use for 2 motors PE4_PWM1, PE5_PWM2
//!
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void OpenServo(void)
{
	if(ui8ServoStatus==EnableServo)
	{
		ui8AdjustServo=Open;
		PWMGenDisable(PWM1_BASE, PWM_GEN_0);
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,  ui8AdjustServo * ui32ServoPeriod / 1000);
		PWMGenEnable(PWM1_BASE, PWM_GEN_0);
	}
}
//*****************************************************************************
//
//! Config PWM: use for 2 motors PE4_PWM1, PE5_PWM2
//!
//!
//! \param None.
//!
//! \return None.
//
//*****************************************************************************
void CloseServo(void)
{
	if(ui8ServoStatus==EnableServo)
	{
		ui8AdjustServo=Close;
		PWMGenDisable(PWM1_BASE, PWM_GEN_0);
		PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0,  ui8AdjustServo * ui32ServoPeriod / 1000);
		PWMGenEnable(PWM1_BASE, PWM_GEN_0);
	}
}
