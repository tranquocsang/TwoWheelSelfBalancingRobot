/*
 * MyServo.h
 *
 *  Created on: Jul 20, 2015
 *      Author: Bach
 */

#ifndef MYSERVO_H_
#define MYSERVO_H_

#define PWM_FREQUENCY 50
#define EnableServo 1
#define DisableServo 0
#define Open		100
#define Close		40

#define SERVO_DISABLE     PWMGenDisable(PWM1_BASE, PWM_GEN_0)
#define SERVO_ENABLE	  PWMGenEnable(PWM1_BASE, PWM_GEN_0)

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
void ConfigServo(void);
void ControlServo(uint8_t ui8AdjustServo);
void OpenServo(void);
void CloseServo(void);



#endif /* MYSERVO_H_ */
