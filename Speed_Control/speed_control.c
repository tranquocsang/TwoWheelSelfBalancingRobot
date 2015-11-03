/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *	version 0.0.1
 */

/**
 * @file	speed control.c
 * @brief	speed control
 */

#include "../include.h"
#include "speed_control.h"

//* Private function prototype ----------------------------------------------*/
void Config_PWM(void);
void SetPWM_MotorLeft(int32_t ucDutyCycle, float Left_Factor);
void SetPWM_MotorRight(int32_t ucDutyCycle, float Right_Factor);
//* Private variables -------------------------------------------------------*/
/********************************************************************************/
static uint32_t ui32PWM_Period = 0;
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
void Config_PWM()
{
	//Configure PWM clock to match system
	SysCtlPWMClockSet(SYSCTL_PWMDIV_8);

	//Enable the peripherals used by this program.
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);//Tiva Launchpad has 2 modules (0 and 1) and module 1 covers led pins
	SysCtlPeripheralEnable(PERIPH_PWM);
	ui32PWM_Period = (SysCtlPWMClockGet()/PWM_FRQ);//PWM frequency ?Khz

	//Configure PE4 ; PE5 pins as PWM
	GPIOPinConfigure(PIN_PWM_LEFT);
	GPIOPinConfigure(PIN_PWM_RIGHT);

	GPIOPinTypePWM(PWM_PORT_BASE, PWM_OUT_LEFT | PWM_OUT_RIGHT);

	//Configure PC5 ; PC6  as GPIO DIRE
	 //PortC Enable
	 SysCtlPeripheralEnable(PERIPH_DIR);
	 GPIOPinTypeGPIOOutput(MOTOR_DIR_BASE,MOTOR_LEFT | MOTOR_RIGHT );

	//Configure PWM Options
	PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
	PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, ui32PWM_Period -1);

	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, 1);
	PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, 1);

	//Turn on the Output pins
	PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
	PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);

	//Enable the PWM generator
	ENABLE_PWM();
}
/*********************************************************************************/
void SetPWM_MotorLeft(int32_t ucDutyCycle,	const float Left_Factor)
{
	if(ucDutyCycle > 0)
	{
		MotorLeft_GoStraight();
	}
	else if(ucDutyCycle < 0)
	{
		MotorLeft_GoBack();
	}
	else
	{
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,1);
		DISSABLE_PWM();
	}
	ucDutyCycle = abs(ucDutyCycle);
	if(ucDutyCycle>75) ucDutyCycle = 75;
	if(ucDutyCycle<5)
	{
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4,1);
		DISSABLE_PWM();
//		LED_GREEN_OFF;
	}
	else
	{
		ucDutyCycle = (uint32_t)(ucDutyCycle * Left_Factor);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, ucDutyCycle * ui32PWM_Period / 100 - 1);
		ENABLE_PWM();
//		LED_GREEN_ON;
	}
}
/*********************************************************************************/
void SetPWM_MotorRight(int32_t ucDutyCycle, const float Right_Factor)
{
	if(ucDutyCycle > 0)
	{
		MotorRight_GoStraight();

	}
	else if(ucDutyCycle < 0)
	{
		MotorRight_GoBack();
	}
	else
	{
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5,1);
		DISSABLE_PWM();
//		LED_GREEN_OFF;
	}
	ucDutyCycle = abs(ucDutyCycle);
	if(ucDutyCycle>75) ucDutyCycle = 75;
	if(ucDutyCycle<5)
	{
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5,1);
		DISSABLE_PWM();
//		LED_GREEN_OFF;
	}
	else
	{
		ucDutyCycle = (uint32_t)(ucDutyCycle * Right_Factor);
		PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, ucDutyCycle * ui32PWM_Period / 100 - 1);
		ENABLE_PWM();
//		LED_GREEN_ON;
	}
}
