/**
 *	Raise your ARM 2015 sample code http://raiseyourarm.com/
 *	Author: Pay it forward club
 *	http://www.payitforward.edu.vn
 *  version 0.0.1
 */

/**
 * @file	SystemConfig.h
 * @brief	Config system
 */

#ifndef SYSTEMCONFIG_H_
#define SYSTEMCONFIG_H_

extern void Config_System(void);
extern uint32_t Get_tick();


extern void Togle(uint8_t LED, uint32_t ms_delay);
extern void ConfigButtons(void);
extern void ButtonsISR(void);
extern void Button1ISR(void);
extern void Button2ISR(void);

#endif /* SYSTEMCONFIG_H_ */
