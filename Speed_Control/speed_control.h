/*
 * speed_control.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Bach
 */

#ifndef SPEED_CONTROL_SPEED_CONTROL_H_
#define SPEED_CONTROL_SPEED_CONTROL_H_

#define PWM_FRQ						3000  // ???1000 ???20000

#define ENABLE_PWM()				PWMGenEnable(PWM0_BASE, PWM_GEN_2)
#define DISSABLE_PWM()				PWMGenDisable(PWM0_BASE, PWM_GEN_2)

#define MOTOR_DIR_BASE				GPIO_PORTC_BASE
#define PERIPH_DIR					SYSCTL_PERIPH_GPIOC
#define MOTOR_LEFT					GPIO_PIN_5
#define MOTOR_RIGHT					GPIO_PIN_6

#define MotorLeft_GoStraight() 		GPIOPinWrite(MOTOR_DIR_BASE, MOTOR_LEFT,0xff)
#define MotorRight_GoStraight() 	GPIOPinWrite(MOTOR_DIR_BASE, MOTOR_RIGHT,0xff)

#define MotorLeft_GoBack() 			GPIOPinWrite(MOTOR_DIR_BASE, MOTOR_LEFT,0x00)
#define MotorRight_GoBack() 		GPIOPinWrite(MOTOR_DIR_BASE, MOTOR_RIGHT,0x00)

#define PERIPH_PWM					SYSCTL_PERIPH_GPIOE
#define PWM_PORT_BASE				GPIO_PORTE_BASE

#define PWM_OUT_LEFT				GPIO_PIN_4
#define PWM_OUT_RIGHT				GPIO_PIN_5

#define PIN_PWM_LEFT				GPIO_PE4_M0PWM4
#define PIN_PWM_RIGHT				GPIO_PE5_M0PWM5

/***************************************************************/
extern void Config_PWM(void);
extern void SetPWM_MotorLeft(int32_t ucDutyCycle, float Left_Factor);
extern void SetPWM_MotorRight(int32_t ucDutyCycle, float Right_Factor);


#endif /* SPEED_CONTROL_SPEED_CONTROL_H_ */
