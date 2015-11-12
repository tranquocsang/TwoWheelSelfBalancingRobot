/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	PID.c
 * @brief	PID wall controller
 */

#include "../include.h"
#include "PID.h"

PID_PARAMETERS PID_Small_Angle = {.Kp = 23.0, .Kd = 3.0, .Ki =5.0,
		.Ts = 0.015, .PID_Saturation = 90, .Const_K = 1.11, .e_=0.0, .e__=0.0, .u_=0.0};
		
PID_PARAMETERS PID_Big_Angle = {.Kp = 23.0, .Kd = 3.0, .Ki =5.0,
		.Ts = 0.015, .PID_Saturation = 90, .Const_K = 1.11, .e_=0.0, .e__=0.0, .u_=0.0};
//* Private variables -------------------------------------------------------*/
/**
 * @brief set params for PID controller
 */
void pid_set_k_params(PID_PARAMETERS* pid_parameter,float Kp,float Ki, float Kd)
{
	pid_parameter->Kp = Kp;
	pid_parameter->Ki = Ki;
	pid_parameter->Kd = Kd;
}
/*
 * @brief calculate PID
 * @param pid_parmeter pointer to PID parameter
 * @param error	input error
 * @return PID controler output
 */
double pid_process(PID_PARAMETERS* pid_parameter, float Current_Angle, float Target_Angle)
{

	float error = (float)(Target_Angle - Current_Angle);

	pid_parameter->e__ = pid_parameter->e_;
	pid_parameter->e_ = pid_parameter->e;
	pid_parameter->e = error;
	pid_parameter->u_ = pid_parameter->u;
	pid_parameter->u = pid_parameter->u_ + pid_parameter->Kp * (pid_parameter->e - pid_parameter->e_)
			+ pid_parameter->Ki * pid_parameter->Ts * pid_parameter->e
			+ (pid_parameter->Kd / pid_parameter->Ts) * (pid_parameter->e - (2 * pid_parameter->e_) + pid_parameter->e__);

	if (pid_parameter->u > pid_parameter->PID_Saturation)
	{
		pid_parameter->u = pid_parameter->PID_Saturation;
	}
	else if (pid_parameter->u < (-pid_parameter->PID_Saturation))
	{
		pid_parameter->u = -pid_parameter->PID_Saturation;
	}

	return (pid_parameter->Const_K * pid_parameter->u);
}

/**
 * @brief reset PID controller
 */
void pid_reset(PID_PARAMETERS* pid_parameter)
{
	pid_parameter->e = 0;
	pid_parameter->e_ = 0;
	pid_parameter->e__ = 0;
	pid_parameter->u = 0;
	pid_parameter->u_ = 0;
}
