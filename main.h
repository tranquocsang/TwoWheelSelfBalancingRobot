/*
 * main.h
 *
 *  Created on: Nov 11, 2015
 *      Author: Bach
 */

#ifndef MAIN_H_
#define MAIN_H_

void Process_Balancing(void);
void Process_Balancing_Complementary_Filter();
void Process_Balancing_2nd_Complementary_Filter();
void Process_Balancing_Kalman_Filter();
int8_t Check_Postive_Sig(double Data);

extern void Test_ENC();


#endif /* MAIN_H_ */
