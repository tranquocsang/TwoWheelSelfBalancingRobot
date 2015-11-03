/*
 * Kalman_Filter.c
 *
 *  Created on: Nov 1, 2015
 *      Author: Bach
 */

#include "../include.h"
#include "Kalman_Filter.h"


extern float Acc_X_angle, Acc_Y_angle;
extern float Gyro_X_rate , Gyro_Y_rate;
extern float X_angle, Y_angle;			 // using float or double?????

// KasBot V2  -  Kalman filter module - http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1284738418 - http://www.x-firm.com/?page_id=145
//with slightly modifications by Kristian Lauszus

#ifdef _USE_Kalman_X_Filter_

float Q_angleX  =  0.001;
float Q_gyroX   =  0.003;
float R_angleX  =  0.03;

float X_bias = 0;
float PX_00 = 0, PX_01 = 0, PX_10 = 0, PX_11 = 0;
float yX, SX;
float KX_0, KX_1;

float Kalman_X_Filter(float newAngle, float newRate, float dt)
{
    X_angle +=    dt * (newRate - X_bias);

    PX_00 	+=  - dt * (PX_10 + PX_01) + Q_angleX * dt;
    PX_01 	+=  - dt * PX_11;
    PX_10 	+=  - dt * PX_11;
    PX_11 	+=  + Q_gyroX * dt;

    yX = newAngle - X_angle;
    SX = PX_00 + R_angleX;
    KX_0 = PX_00 / SX;
    KX_1 = PX_10 / SX;

    X_angle +=  KX_0 * yX;
    X_bias  +=  KX_1 * yX;
    PX_00 -= KX_0 * PX_00;
    PX_01 -= KX_0 * PX_01;
    PX_10 -= KX_1 * PX_00;
    PX_11 -= KX_1 * PX_01;

    return X_angle;
}
#endif
/*******************************************************************************/
#ifdef _USE_Kalman_Y_Filter_
// KasBot V2  -  Kalman filter module - http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1284738418 - http://www.x-firm.com/?page_id=145
//with slightly modifications by Kristian Lauszus

float Q_angleY  =  0.001;
float Q_gyroY   =  0.003;
float R_angleY  =  0.03;

float Y_bias = 0;
float PY_00 = 0, PY_01 = 0, PY_10 = 0, PY_11 = 0;
float yY, SY;
float KY_0, KY_1;

float Kalman_Y_Filter(float newAngle, float newRate, float dt)
{
    Y_angle += dt * (newRate - Y_bias);
    PY_00 +=  - dt * (PY_10 + PY_01) + Q_angleY * dt;
    PY_01 +=  - dt * PY_11;
    PY_10 +=  - dt * PY_11;
    PY_11 +=  + Q_gyroY * dt;

    yY = newAngle - Y_angle;
    SY = PY_00 + R_angleY;
    KY_0 = PY_00 / SY;
    KY_1 = PY_10 / SY;

    Y_angle +=  KY_0 * yY;
    Y_bias  +=  KY_1 * yY;
    PY_00 -= KY_0 * PY_00;
    PY_01 -= KY_0 * PY_01;
    PY_10 -= KY_1 * PY_00;
    PY_11 -= KY_1 * PY_01;

    return Y_angle;
}
#endif

