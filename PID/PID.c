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

const float Const_K = 1.2;
PID_PARAMETERS PID1 = {.Kp = 2.0, .Kd = 0.9, .Ki =0.0,
		.Ts = 0.01, .PID_Saturation = 70, .e_=0.0, .e__=0.0, .u_=0.0};
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

	return (Const_K * pid_parameter->u);
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
