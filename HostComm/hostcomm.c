/*
 * HostComm.c
 *
 *  Created on: Jul 14, 2015
 *      Author: Huan
 *      Modify :Kanh->>>>
 */

#include "../include.h"
//   start|| srcid || dest_id||
enum MSG_CODE
{
        MSG_UPDATE_POS=0,
        MSG_TIME,
        MSG_BOX,
        MSG_WAYPOINT,
        MSG_TRACK_BOT,
        MSG_UPDATE_BOT,
        MSG_SPEED_SET,  //6
        MSG_START_TEST,
        MSG_SET_PID,
        MSG_IMG_UPDATE=10,
		MSG_EMC_STOP=11,
		MSG_EMC_START=12,
		MSG_EMC_SWF_R=13,
		MSG_EMC_SWF_L=14,
		MSG_EMC_IMG_SOLVE = 15,
};
bool HostComm_Process_Flag = false;
bool     HostComm_Enable_Timer_Flag = true;
uint32_t HostComm_Timer_Counter = 0;

static uint32_t rcvMsgByte=0;  // byte nhan ve
static uint8_t rcvMsg[MAX_MSG_LEN_BYTE];
static uint32_t rcvMsgLen=0;  //

static uint8_t data[MAX_MSG_LEN_BYTE];  // du lieu duoc luu trong mang data[] -> voi kich thuowcs nhan ve
static int32_t len;

void HostCommInit()
{
        bluetooth_init(115200);

#ifdef _USE_HOSTCOMM_
        HostComm_Enable_Timer_Flag = true;
        HostComm_Timer_Counter = 0;
        HostComm_Process_Flag = false;
#endif
}
uint16_t calcCheckSum(uint8_t *data, uint8_t len)
{
    uint16_t sum=0;
    int i;
    for (i=0; i<len; i++)
    {
        sum+=data[i];
    }
    return sum;
}
static COMM_RESULT handleMsg(int msgCode,uint8_t* payload)
{

//        switch (msgCode)
//        {
//        	case MSG_SPEED_SET:
//        	break;
//        }
        return SUCCESS;
}
COMM_RESULT HostComm_process(void)  // chuong trinh nhan tin hieu
{
      //0xa5 +length 2 +msg type 1+src id 1+dest id 1+msg id 1+payload (số lượng Byte phụ thuộc)+crc 2+0xd
      if (HostComm_Process_Flag == true)
        {
          HostComm_Process_Flag = false;
          len=bluetooth_recv(data,MAX_MSG_LEN_BYTE,false);// len la tong du lieu nhan ve ->
          if (len)
          {
        	  int i;
        	  for (i=0;i<len;i++)
        	  {
        		  if (rcvMsgByte==0)  //    byte nhan ve ban dau bang 0
        		  {
        			  if (data[i]==START_BYTE)// neu byte thu i la 0xa5
        			  {
						rcvMsg[rcvMsgByte++] = data[i];  // gan Start_byte vao trong rcvMsg->
        			  }
        			  continue;
        		  }
        		  rcvMsg[rcvMsgByte++] = data[i];  // gan data vao trong rcvMsg
        		  if (rcvMsgByte==3)
        		  {
        			  rcvMsgLen = rcvMsg[1] + (rcvMsg[2]<<8) + 6;
        			  if (rcvMsgLen<MIN_MSG_LEN_BYTE)
        			   {
        				  rcvMsgByte = 0;
        				  return LENGTH_ERROR;
        			   }
        		  }
        		  if (rcvMsgByte==rcvMsgLen)
        		  {
        			  uint16_t crc;
        			  rcvMsgByte = 0;
        			  crc=calcCheckSum(data+3,rcvMsgLen-6);
        			  if (crc != (data[rcvMsgLen-3]|(data[rcvMsgLen-2]<<8)))
						return CRC_ERROR;
        			  if (rcvMsg[rcvMsgLen-1]!=END_BYTE)
						return ENDBYTE_ERROR;
        			  return handleMsg(rcvMsg[3],rcvMsg+7);  //kaka chu y cai nay
        		  }
        	  }
          }
        }
        return INCOMPLETE_MSG;
}
