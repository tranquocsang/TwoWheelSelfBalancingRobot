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

typedef enum
{
	SYSTEM_POWER_UP = 0,
	SYSTEM_INITIALIZE,
	SYSTEM_CALIB_MPU6050,
	SYSTEM_GET_MOTOR_MODEL,
	SYSTEM_ESTIMATE_MOTOR_MODEL,
	SYSTEM_SAVE_MOTOR_MODEL,
	SYSTEM_LOAD_MOTOR_MODEL,
	SYSTEM_WAIT_TO_RUN,
	SYSTEM_SLEEP,
	SYSTEM_WAKE_UP,
	SYSTEM_ACTIVE,
	SYSTEM_ERROR,

	SYSTEM_TEST_ENC
} SYSTEM_STATE;

extern void Config_System(void);
extern SYSTEM_STATE system_GetState(void);
extern void system_SetState(SYSTEM_STATE SysState);
extern void system_Process_System_State(void);
extern uint32_t Get_tick();
extern uint32_t u32_UsrSystemClockGet();

extern void Togle(uint8_t LED, uint32_t ms_delay);

extern void ButtonLeftHandler(void);
extern void ButtonRightHandler(void);

#endif /* SYSTEMCONFIG_H_ */
