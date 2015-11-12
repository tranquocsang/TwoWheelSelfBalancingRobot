/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *	version 0.0.1
 */

/**
 * @file	speed_control.h
 * @brief	speed control
 */


#ifndef STR_SPEED_CONTROL_H_
#define STR_SPEED_CONTROL_H_

#define PWM_MOTOR_LEFT			PWM0_BASE, PWM_OUT_4
#define PWM_MOTOR_RIGHT			PWM0_BASE, PWM_OUT_5

#define PWM_FRQ						4000  // ???1000 ???20000

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

typedef enum
{
	MOTOR_Left = 0,
	MOTOR_Right
}MOTOR_SELECT;

extern void speed_control_init(void);
extern void ProcessSpeedControl(void);
extern void speed_set(MOTOR_SELECT Select, int32_t speed);

extern void speed_SetMotorModel(MOTOR_SELECT select, real_T Theta[4]);
extern void speed_GetMotorModel(MOTOR_SELECT select, real_T Theta[4]);

extern void SetPWM_MotorLeft(int32_t ucDutyCycle, float Left_Factor,int32_t Saturation_Left_PWM);
extern void SetPWM_MotorRight(int32_t ucDutyCycle, float Right_Factor,int32_t Saturation_Right_PWM);

#endif /* STR_SPEED_CONTROL_H_ */
