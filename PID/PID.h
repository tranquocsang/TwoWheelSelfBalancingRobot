/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	PID.h
 * @brief	PID wall controller
 */


#ifndef WALLFOLLOW_PID_H_
#define WALLFOLLOW_PID_H_

typedef struct
{
	float Kp;
	float Ki;
	float Kd;
	double u;
	double u_;
	float e;
	float e_;
	float e__;
	float Ts;
	float PID_Saturation;
} PID_PARAMETERS;

extern void pid_init(void);
extern void pid_set_parameters(PID_PARAMETERS pid_param);
double pid_process(PID_PARAMETERS* pid_parameter, float Current_Angle, float Target_Angle);
extern float pid_get_error();
extern void pid_reset();
extern void pid_set_k_params(PID_PARAMETERS* pid_parameters,float Kp,float Ki, float Kd);
extern void pid_get_parameters(PID_PARAMETERS *pid_param);

#endif /* WALLFOLLOW_PID_H_ */
