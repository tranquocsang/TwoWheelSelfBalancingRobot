/*
 * HostComm.h
 *
 *  Created on: Jul 15, 2015
 *      Author: Huan
 */

#ifndef HOSTCOMM_H_
#define HOSTCOMM_H_

#define UPDATE_TIME_MS 50
#define MAX_MSG_LEN_BYTE 50
#define MIN_MSG_LEN_BYTE 6
#define START_BYTE 0xA5

#define SRC_ID 1//robot
#define DEST_ID 0//PC

#define END_BYTE 0x0D

typedef enum
{
	INCOMPLETE_MSG=0,
	LENGTH_ERROR,
	CRC_ERROR,
	ENDBYTE_ERROR,
	SUCCESS
}COMM_RESULT;

void HostCommInit();
COMM_RESULT HostComm_process(void);

#endif /* HOSTCOMM_H_ */
