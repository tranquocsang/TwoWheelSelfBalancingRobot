/*
 * define.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Bach
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#define _USE_KALMAN_FILTER_
//#define _USE_COMPLEMENTARY_FILTER_
//#define _USE_2ND_COMPLEMENTARY_FILTER_


//*****************************************************************************
//
// Define some values of System
//
//*****************************************************************************
#define LED_PERIPHERAL      	SYSCTL_PERIPH_GPIOF
#define BUTTON_PERIPHERAL   	SYSCTL_PERIPH_GPIOF
#define TIMER0_PERIPHERAL   	SYSCTL_PERIPH_TIMER0
#define TIMER1_PERIPHERAL   	SYSCTL_PERIPH_TIMER1
/*****************************************************************************/
#define LED_PORT    			GPIO_PORTF_BASE
#define BUTTON_PORT 			GPIO_PORTF_BASE
#define LED_RED					GPIO_PIN_1
#define LED_GREEN				GPIO_PIN_3
#define LED_BLUE				GPIO_PIN_2
#define LED_OFF     			0x00
/*****************************************************************************/
#define SW1						GPIO_PIN_4
#define SW2 					GPIO_PIN_0

#define LED_RED_ON				GPIOPinWrite(LED_PORT,  LED_RED, LED_RED)
#define LED_GREEN_ON			GPIOPinWrite(LED_PORT,  LED_GREEN, LED_GREEN)
#define LED_BLUE_ON				GPIOPinWrite(LED_PORT,  LED_BLUE, LED_BLUE)

#define LED_RED_OFF				GPIOPinWrite(LED_PORT,  LED_RED, LED_OFF)
#define LED_GREEN_OFF			GPIOPinWrite(LED_PORT,  LED_GREEN, LED_OFF)
#define LED_BLUE_OFF			GPIOPinWrite(LED_PORT,  LED_BLUE, LED_OFF)


#endif /* DEFINE_H_ */
