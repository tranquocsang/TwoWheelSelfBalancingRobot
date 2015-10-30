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

//* Private variables -------------------------------------------------------*/
void Config_System(void)
{
//	ROM_FPUEnable();
//	ROM_FPULazyStackingEnable();
	// Config clock
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	//
}

