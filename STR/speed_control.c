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
static void speed_update_setpoint(void);
static void speed_control_runtimeout(uint32_t ms);
static void speed_control_stoptimeout(void);

void SetPWM_MotorLeft(int32_t ucDutyCycle, float Left_Factor,int32_t Saturation_Left_PWM);
void SetPWM_MotorRight(int32_t ucDutyCycle, float Right_Factor,int32_t Saturation_Right_PWM);

//* Private variables -------------------------------------------------------*/
static real_T Theta[4], Theta_[4] = {-1, 1, 1, 1};
static real_T Theta2[4], Theta2_[4] = {-1, 1, 1, 1};
static int32_t SetPoint[2] = {0, 0};
static int32_t RealSpeedSet[2] = {0, 0};
static float udk = 0;
static TIMER_ID speed_control_timID = INVALID_TIMER_ID;


static uint32_t ui32PWM_Period = 0;
void speed_control_init(void)
{
	Control_initialize();
	Config_PWM();
	SetPWM_MotorRight(1,1.0,90);
	SetPWM_MotorLeft(1,1.0,90);
}

/**
 * @brief Init battery sense
 * @note this function must call to calculate speed control
 */
void ProcessSpeedControl(void)
{
	int32_t Velocity[2];
//	SetPoint = 250;
	if (qei_getVelocity(0, &Velocity[0]) == true)
	{
		udk = STR_Indirect(Theta, RealSpeedSet[0], Velocity[0]);
		SetPWM_MotorRight(udk,1.0,90);
		Uocluong(udk, Velocity[0], Theta, Theta_);
#ifdef _DEBUG_SPEED_
		bluetooth_print("Right: %d\r\n", Velocity[0]);
#endif
	}
	if (qei_getVelocity(1, &Velocity[1]) == true)
	{
		udk = STR_Indirect2(Theta2, RealSpeedSet[1], Velocity[1]);
		SetPWM_MotorLeft(udk,1.0,90);
		Uocluong2(udk, Velocity[1], Theta2, Theta2_);
#ifdef _DEBUG_SPEED_
		bluetooth_print("Left: %d\r\n", Velocity[1]);
#endif
	}
}

void Config_PWM(void)
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
void SetPWM_MotorLeft(int32_t ucDutyCycle,	const float Left_Factor, int32_t Saturation_Left_PWM)
{
	if(ucDutyCycle > 0)
	{
		MotorLeft_GoStraight();
	}
	else if(ucDutyCycle < 0)
	{
		MotorLeft_GoBack();
	}
	ucDutyCycle = abs(ucDutyCycle);
	if(ucDutyCycle>Saturation_Left_PWM) ucDutyCycle = Saturation_Left_PWM;
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
void SetPWM_MotorRight(int32_t ucDutyCycle, const float Right_Factor, int32_t Saturation_Right_PWM)
{
	if(ucDutyCycle > 0)
	{
		MotorRight_GoStraight();

	}
	else if(ucDutyCycle < 0)
	{
		MotorRight_GoBack();
	}

	ucDutyCycle = abs(ucDutyCycle);
	if(ucDutyCycle>Saturation_Right_PWM) ucDutyCycle = Saturation_Right_PWM;
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
/**
 * @brief Control speed
 * @param select motor select
 * @param speed motor speed (encoder pulse / 20ms)
 */
void speed_set(MOTOR_SELECT Select, int32_t speed)
{
	//speed_Enable_Hbridge(true);
	if (Select == MOTOR_Right)
	{
		if (SetPoint[0] != speed)
		{
			SetPoint[0] = speed;
			speed_control_runtimeout(20);
		}
	}
	else if (Select == MOTOR_Left)
	{
		if (SetPoint[1] != speed)
		{
			SetPoint[1] = speed;
			speed_control_runtimeout(20);
		}
	}
}


static void speed_update_setpoint(void)
{
	int i;
	speed_control_timID = INVALID_TIMER_ID;

	for (i = 0; i < 2; i++)
	{
		if (RealSpeedSet[i] + 20 < SetPoint[i])
			RealSpeedSet[i] += 20;
		else if (RealSpeedSet[i] > SetPoint[i] + 20)
			RealSpeedSet[i] -= 20;
		else
			RealSpeedSet[i] = SetPoint[i];
	}

	speed_control_runtimeout(20);
}

static void speed_control_runtimeout(uint32_t ms)
{
	speed_control_stoptimeout();
	speed_control_timID = TIMER_RegisterEvent(&speed_update_setpoint, ms);
}

static void speed_control_stoptimeout(void)
{
	if (speed_control_timID != INVALID_TIMER_ID)
		TIMER_UnregisterEvent(speed_control_timID);
	speed_control_timID = INVALID_TIMER_ID;
}

void speed_SetMotorModel(MOTOR_SELECT select, real_T Theta[4])
{
	int i;
	if (select == MOTOR_Right)
	{
		for (i = 0; i < 4; i++)
		{
			Theta_[i] = Theta[i];
		}
	}
	else if (select == MOTOR_Left)
	{
		for (i = 0; i < 4; i++)
		{
			Theta2_[i] = Theta[i];
		}
	}
}

void speed_GetMotorModel(MOTOR_SELECT select, real_T Theta[4])
{
	int i;
	if (select == MOTOR_Right)
	{
		for (i = 0; i < 4; i++)
		{
			Theta[i] = Theta_[i];
		}
	}
	else if (select == MOTOR_Left)
	{
		for (i = 0; i < 4; i++)
		{
			Theta[i] = Theta2_[i];
		}
	}
}
