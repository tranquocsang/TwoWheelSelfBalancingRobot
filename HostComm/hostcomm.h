/*
 * HostComm.h
 *
 *  Created on: Jul 15, 2015
 *      Author: Huan
 */

#ifndef HOSTCOMM_H_
#define HOSTCOMM_H_

#define UPDATE_TIME_MS 10000
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

typedef enum
{
	DungYen_XoayTrai = 1,
	VuaDi_VuaXoayTrai=2,
	DungYen_XoayPhai=3,
	VuaDi_VuaXoayPhai=4,
	DungYen_XoayTrai_toi = 5,
	VuaDi_VuaXoayTrai_toi=6,
	DungYen_XoayPhai_toi=7,
	VuaDi_VuaXoayPhai_toi=8,
	Img_NONE=254,
}IMG_MODE;

void HostCommInit();
COMM_RESULT HostComm_process(void);

#endif /* HOSTCOMM_H_ */
