/*
 * Kalman_Filter.h
 *
 *  Created on: Nov 1, 2015
 *      Author: Bach
 */

#ifndef KALMAN_FILTER_KALMAN_FILTER_H_
#define KALMAN_FILTER_KALMAN_FILTER_H_

#define _USE_Kalman_X_Filter_
#define _USE_Kalman_Y_Filter_

#ifdef _USE_Kalman_X_Filter_
extern float Kalman_X_Filter(float newAngle, float newRate, float dt);
#endif

#ifdef _USE_Kalman_Y_Filter_
extern float Kalman_Y_Filter(float newAngle, float newRate, float dt);
#endif

#endif /* KALMAN_FILTER_KALMAN_FILTER_H_ */
