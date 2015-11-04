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
//* Private variables -------------------------------------------------------*/
//* Global variables -------------------------------------------------------*/
uint32_t ms_Tickcount=0;
bool bool_Process_Flag = false;
uint32_t Get_tick();

uint32_t Counter_Togle_Led = 0;

void ConfigButtons(void);
void ButtonsISR(void);
void Button1ISR(void);
void Button2ISR(void);

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

	ConfigButtons();


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
 * -- ConfigButtons(void) --------------------------------------
 *
 * Description	:
 * Parameters	: none
 * Return		: don't care
 */
void ConfigButtons(void)
{
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;		//Unlock PF0 for using SW2
	HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
	HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0 ;

	SysCtlPeripheralEnable(BUTTON_PERIPHERAL);
	GPIODirModeSet(BUTTON_PORT, SW1|SW2, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(BUTTON_PORT, SW1|SW2, GPIO_STRENGTH_8MA,
				         GPIO_PIN_TYPE_STD_WPU);

	GPIOIntTypeSet(BUTTON_PORT,SW1|SW2, GPIO_FALLING_EDGE);		//Configure GPIO Interrupt for SW1, SW2
	GPIOIntRegister(BUTTON_PORT,&ButtonsISR);
	GPIOIntEnable(BUTTON_PORT, SW1|SW2);
	IntEnable(INT_GPIOF);
	GPIOIntClear(BUTTON_PORT, SW1|SW2);
}
/******************************************************************************
 * --------------- void ButtonISR1(void) --------------------------------------
 *
 * Description	:
 * Parameters	: none
 * Return		: don't care
 */
void Button1ISR(void)
{
	GPIOIntClear(BUTTON_PORT, SW1);									    // Clear the Button interrupt
	SysCtlDelay(SysCtlClockGet()/3/10);

	/*************write ur code here****************/
}
/******************************************************************************
 * --------------- void Button2ISR(void) --------------------------------------
 *
 * Description	:
 * Parameters	: none
 * Return		: don't care
 */
void Button2ISR(void)
{
	GPIOIntClear(BUTTON_PORT, SW2);									    // Clear the Button interrupt
	SysCtlDelay(SysCtlClockGet()/3/10);

	/*****************Write ur code here*********************************/
}
//*****************************************************************************
//
//! GPIO  Interrupt Service Routine  for two button of main board.
//!
//! \param None
//!
//! \return None
//
//*****************************************************************************
void ButtonsISR(void)
{
	uint32_t ui32Status;
	ui32Status = GPIOIntStatus(BUTTON_PORT,true);
	GPIOIntClear(BUTTON_PORT, ui32Status);
	if (ui32Status & SW1)
	{
		Button1ISR();
	}
	else if (ui32Status & SW2)
	{
		Button2ISR();
	}
}
/****************************************************************************** */
