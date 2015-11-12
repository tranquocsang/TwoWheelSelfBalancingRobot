/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	SystemConfig.c
 * @brief	System config
 */
#include "include.h"
#include "inc/hw_gpio.h"
#include "driverlib/systick.h"

//* Private function prototype ----------------------------------------------*/
static void system_SystickConfig(uint32_t ui32_msInterval);
static void SysTickIntHandle(void);
static SYSTEM_STATE e_SystemState = SYSTEM_POWER_UP;
//* Private variables -------------------------------------------------------*/
//* Global variables -------------------------------------------------------*/
uint32_t ms_Tickcount=0;
bool bool_Process_Flag = false;
uint32_t Get_tick();

uint32_t Counter_Togle_Led = 0;

static uint32_t systemClock = 80000000;
uint32_t u32_UsrSystemClockGet();
void system_SetState(SYSTEM_STATE SysState);

uint32_t u32_UsrSystemClockGet()
{
	return systemClock;
}

/*****************************************************************************/
void Config_System(void)
{
	// Config clock
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	ROM_FPUEnable();
	ROM_FPULazyStackingEnable();

	SysCtlPeripheralEnable(LED_PERIPHERAL);                             // Enable LEDs
	GPIOPinTypeGPIOOutput(LED_PORT, LED_RED|LED_GREEN|LED_BLUE);        // Configure GPIO that connect to LED - PIN 1,2,3

	LED_RED_OFF;
	LED_GREEN_OFF;
	LED_BLUE_OFF;

#ifdef _USE_KALMAN_FILTER_
	system_SystickConfig(1);
#endif

#ifdef _USE_COMPLEMENTARY_FILTER_
	system_SystickConfig(1);
#endif

#ifdef _USE_2ND_COMPLEMENTARY_FILTER_
	system_SystickConfig(1);
#endif
}
/*****************************************************************************/
static void system_SystickConfig(uint32_t ui32_msInterval)
{
	ROM_SysTickPeriodSet(ROM_SysCtlClockGet() * ui32_msInterval / 1000);
	SysTickIntRegister(&SysTickIntHandle);
	ROM_SysTickIntEnable();
	ROM_SysTickEnable();
}
/*****************************************************************************/
static void SysTickIntHandle(void)
{
	ms_Tickcount++;
	bool_Process_Flag = true;
}
/*****************************************************************************/
uint32_t Get_tick()
{
	return ms_Tickcount;
}

/*****************************************************************************
 * ------------------------Togle LED()
 *
 */
void Togle(uint8_t LED, uint32_t ms_delay)
{
	static uint8_t LED_Status;
	if(Counter_Togle_Led > ms_delay)
	{
		Counter_Togle_Led = 0;
		LED_Status ^= LED;
		GPIOPinWrite(LED_PORT,  LED, LED_Status);
	}
}

/****************************************************************************/
/******************************************************************************
 * --------------- void ButtonISR1(void) --------------------------------------
 *
 * Description	:
 * Parameters	: none
 * Return		: don't care
 */
void ButtonLeftHandler(void)
{
	/*************write ur code here****************/
	switch (system_GetState())
	{
		case SYSTEM_INITIALIZE:
			DISSABLE_PWM();
			bluetooth_print("Get motor model \n");
			system_SetState(SYSTEM_GET_MOTOR_MODEL);
			break;

		case SYSTEM_GET_MOTOR_MODEL:
			system_SetState(SYSTEM_ESTIMATE_MOTOR_MODEL);
			bluetooth_print("Estimate motor model \n");
			ENABLE_PWM();
			speed_set(MOTOR_Left,100);
			speed_set(MOTOR_Right,100);
			break;

		case SYSTEM_LOAD_MOTOR_MODEL:
			loadMotorModel();
			system_SetState(SYSTEM_WAIT_TO_RUN);
			break;

		case SYSTEM_ESTIMATE_MOTOR_MODEL:
			bluetooth_print("Save motor model \n");
			DISSABLE_PWM();
			system_SetState(SYSTEM_SAVE_MOTOR_MODEL);
			break;

		case SYSTEM_SAVE_MOTOR_MODEL:
			bluetooth_print("Wait to run \n");
			saveMotorModel();
			system_SetState(SYSTEM_WAIT_TO_RUN);
			break;

		case SYSTEM_WAIT_TO_RUN:
			bluetooth_print("Sleep \n");
			system_SetState(SYSTEM_SLEEP);
			DISSABLE_PWM();
			LED_BLUE_ON;
			break;

		case SYSTEM_SLEEP:
			bluetooth_print("Active \n");
			system_SetState(SYSTEM_ACTIVE);
			ENABLE_PWM();
			LED_BLUE_OFF;
			break;

		default:
			break;
	}
}
/******************************************************************************
 * --------------- void Button2ISR(void) --------------------------------------
 *
 * Description	:
 * Parameters	: none
 * Return		: don't care
 */
void ButtonRightHandler(void)
{
	/*****************Write ur code here*********************************/
}
SYSTEM_STATE system_GetState(void)
{
	return e_SystemState;
}

void system_SetState(SYSTEM_STATE SysState)
{
	e_SystemState = SysState;
}

void system_Process_System_State(void)
{
	switch (system_GetState())
	{
		/********Some test case********/
		case SYSTEM_TEST_ENC:
			Test_ENC();
			break;
		/******************************/
		case SYSTEM_POWER_UP:
			system_SetState(SYSTEM_INITIALIZE);
			break;
		case SYSTEM_INITIALIZE:
			break;
		case SYSTEM_ESTIMATE_MOTOR_MODEL:
			ProcessSpeedControl();
			break;
		case SYSTEM_SAVE_MOTOR_MODEL:
			break;
		case SYSTEM_WAIT_TO_RUN:
			DISSABLE_PWM();
			ProcessSpeedControl();
			break;
		case SYSTEM_SLEEP:
			DISSABLE_PWM();
			ProcessSpeedControl();
			break;
		case SYSTEM_WAKE_UP:
			//LED1_ON();
			ProcessSpeedControl();
			break;
		case SYSTEM_ACTIVE:
			ProcessSpeedControl();
			Process_Balancing();
			break;
		case SYSTEM_ERROR:
			DISSABLE_PWM();
			IntMasterDisable();
			while (1)
			{
				LED_BLUE_ON;
				LED_RED_ON;
				LED_GREEN_ON;
				ROM_SysCtlDelay(ROM_SysCtlClockGet() / 3);
				LED_BLUE_OFF;
				LED_RED_OFF;
				LED_GREEN_OFF;
				ROM_SysCtlDelay(ROM_SysCtlClockGet() / 3);
			}
//			break;
	}
}
