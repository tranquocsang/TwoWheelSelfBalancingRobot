/*
 * Timer.h
 *
 *  Created on: Nov 2, 2015
 *      Author: Bach
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#define TIMER0A_FRQ	100
#define TIMER1A_FRQ 100

extern void Timer0Init(void);
extern void Timer1Init(void);
extern void TIMER0_ISR(void);
extern void TIMER1_ISR(void);

#endif /* TIMER_TIMER_H_ */
