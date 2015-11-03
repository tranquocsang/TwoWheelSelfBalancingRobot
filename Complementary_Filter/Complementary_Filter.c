/*
 * Complementary_Filter.c
 *
 *  Created on: Oct 31, 2015
 *      Author: Bach
 */
#include "../include.h"
#include "Complementary_Filter.h"

#define timeConstant 0.1

//* Private function prototype ----------------------------------------------*/

//* Private variables -------------------------------------------------------*/
//* Global variables -------------------------------------------------------*/

extern float Acc_X_angle, Acc_Y_angle;
extern float Gyro_X_rate , Gyro_Y_rate;
extern float X_angle, Y_angle;			 // using float or double?????




float a = 0.94; //0.9994

float filter_xterm[3] = {0,0,0};
float filter_yterm[3] = {0,0,0};

//Runs a complementary filter configured via float a
float Complementary_X_Filter(float dt)
{
	X_angle = (X_angle + Gyro_X_rate*dt)*a + Acc_X_angle*(1-a);
	return X_angle;
}
float Complementary_Y_Filter(float dt)
{
	Y_angle = (Y_angle + Gyro_Y_rate*dt)*a + Acc_Y_angle*(1-a);
	return Y_angle;
}

//Runs 2nd order complementary filter
float Second_order_Complementary_X_Filter(float dt) //http://code.google.com/p/aeroquad/source/browse/trunk/AeroQuad/Filter.pde?r=143
{
	filter_xterm[0] = (Acc_X_angle - X_angle) * timeConstant * timeConstant;
  	filter_xterm[2] = (dt * filter_xterm[0]) + filter_xterm[2];
  	filter_xterm[1] = filter_xterm[2] + (Acc_X_angle - X_angle) * 2 * timeConstant + Gyro_X_rate;
  	X_angle = (dt * filter_xterm[1]) + X_angle;
  	return X_angle;
}

float Second_order_Complementary_Y_Filter(float dt) //http://code.google.com/p/aeroquad/source/browse/trunk/AeroQuad/Filter.pde?r=143
{
	filter_yterm[0] = (Acc_Y_angle - Y_angle) * timeConstant * timeConstant;
 	filter_yterm[2] = (dt * filter_yterm[0]) + filter_yterm[2];
 	filter_yterm[1] = filter_yterm[2] + (Acc_Y_angle - Y_angle) * 2 * timeConstant + Gyro_Y_rate;
 	Y_angle = (dt * filter_yterm[1]) + Y_angle;
 	return Y_angle;
}


