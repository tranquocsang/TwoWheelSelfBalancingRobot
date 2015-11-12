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
	SIGN_IN=1,
	SIGN_IN_OK=2,
	SIGN_IN_FAIL=3,

	SIGN_UP=4,
	SIGN_UP_OK=5,
	SIGN_UP_FAIL=6,

	WAKE_UP=5,
	WAKE_UP_OK=6,

	MOVE=7,
	MOVE_OK=8,
	MOVE_DONE=9,

	SLEEP=10,
	SLEEP_OK=11,

	TEMP=12,
	TEMP_OK=13
};

static TIMER_ID HostComm_TimerID = INVALID_TIMER_ID;
static bool HostCommFlag = false;

static uint32_t rcvMsgByte=0;  // byte nhan ve
static uint8_t rcvMsg[MAX_MSG_LEN_BYTE];
static uint8_t sendMsg[MAX_MSG_LEN_BYTE];
static uint32_t rcvMsgLen=0;  //

static uint8_t data[MAX_MSG_LEN_BYTE];  // du lieu duoc luu trong mang data[] -> voi kich thuowcs nhan ve
static int32_t len;

void copyToArray(uint8_t *data, uint8_t *x, int len);
void copyFromArray(uint8_t *data, uint8_t *x, int len);
uint8_t prepareData_SignIN(uint8_t *data, uint8_t MSG_CODE, uint8_t *user, uint8_t *password);
uint8_t prepareData_SignUP(uint8_t *data, uint8_t MSG_CODE, uint8_t *user, uint8_t *password);
uint8_t prepareData_Command(uint8_t *data, uint8_t MSG_CODE);
uint8_t prepareData_Temp(uint8_t *data, uint8_t MSG_CODE, uint8_t *temp);

bool Check_User_Password(uint8_t *array_user, uint8_t *array_password);

static void HostCommTimeoutCallBack(void)
{
        HostComm_TimerID = INVALID_TIMER_ID;
        HostCommFlag = true;

        HostComm_process();
        if (HostComm_TimerID != INVALID_TIMER_ID)
                TIMER_UnregisterEvent(HostComm_TimerID);
        HostComm_TimerID = TIMER_RegisterEvent(&HostCommTimeoutCallBack, UPDATE_TIME_MS);
}

void HostCommInit()
{
        bluetooth_init(9600);
        if (HostComm_TimerID != INVALID_TIMER_ID)
                TIMER_UnregisterEvent(HostComm_TimerID);
        HostComm_TimerID = TIMER_RegisterEvent(&HostCommTimeoutCallBack, UPDATE_TIME_MS);
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
	uint8_t array_user[4] = {0};
	uint8_t array_password[4] = {0};
	uint8_t BytesToSend = 0;
        switch (msgCode)
        {
        	case SIGN_IN:

        		copyFromArray(rcvMsg+6, array_user, 4);
				copyFromArray(rcvMsg+10, array_password, 4);

				if(Check_User_Password(array_user, array_password) == true)
        		{
        			BytesToSend = prepareData_SignIN(sendMsg,SIGN_IN_OK, array_user, array_password);
        		}
        		else
        		{
        			BytesToSend = prepareData_SignIN(sendMsg,SIGN_IN_FAIL, array_user, array_password);
        		}
        		bluetooth_sendBytes(sendMsg, BytesToSend);
        	break;

        	case SIGN_UP:
        		copyFromArray(rcvMsg+6, array_user, 4);
				copyFromArray(rcvMsg+10, array_password, 4);

				if(Check_User_Password(array_user, array_password) == true)
				{
					BytesToSend = prepareData_SignUP(sendMsg,SIGN_UP_OK, array_user, array_password);
					Save_User(array_user, array_password);
				}
				else
				{
					BytesToSend = prepareData_SignIN(sendMsg,SIGN_UP_FAIL, array_user, array_password);
				}
				bluetooth_sendBytes(sendMsg, BytesToSend);
        	break;

        	case WAKE_UP:
			break;

        	case MOVE:
			break;

        	case TEMP:
			break;
        }
        return SUCCESS;
}
COMM_RESULT HostComm_process(void)  // chuong trinh nhan tin hieu
{
      //0xa5 +length 2 +msg type 1+src id 1+dest id 1+msg id 1+payload (số lượng Byte phụ thuộc)+crc 2+0xd
      if (HostCommFlag == true)
        {
    	  HostCommFlag = false;
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
        			  return handleMsg(rcvMsg[3],rcvMsg+7);
        		  }
        	  }
          }
        }
        return INCOMPLETE_MSG;
}
/****************************************************************************/
void copyToArray(uint8_t *data, uint8_t *x, int len)
{
	int i=0;
    for (i=0;i<len;i++)
    {
        *data++ = *x++;
    }
}
void copyFromArray(uint8_t *data, uint8_t *x, int len)
{
	int i=0;
    for (i=0;i<len;i++)
    {
        *x++ = *data++;
    }
}
/***************************************************************************/
uint8_t prepareData_SignIN(uint8_t *data, uint8_t MSG_CODE, uint8_t *user, uint8_t *password)
{
    uint8_t index = 0;
    uint16_t crc;
    data[index++]=0xA5;
    data[index++]=0;	//lenght
    data[index++]=0;	//lenght
    data[index++]=MSG_CODE;
    data[index++]=0;	//src id
    data[index++]=1;	//dest id

    copyToArray(data+index,user,4); //4 byte of user
    index+=4;

    copyToArray(data+index,password,4); //4 byte of user
    index+=4;

    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}

/***************************************************************************/
uint8_t prepareData_SignUP(uint8_t *data, uint8_t MSG_CODE, uint8_t *user, uint8_t *password)
{
    uint8_t index = 0;
    uint16_t crc;
    data[index++]=0xA5;
    data[index++]=0;	//lenght
    data[index++]=0;	//lenght
    data[index++]=MSG_CODE;
    data[index++]=0;	//src id
    data[index++]=1;	//dest id

    copyToArray(data+index,user,4); //4 byte of user
    index+=4;

    copyToArray(data+index,password,4); //4 byte of user
    index+=4;

    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}
/***************************************************************************/
uint8_t prepareData_Command(uint8_t *data, uint8_t MSG_CODE)
{
    uint8_t index = 0;
    uint16_t crc;
    data[index++]=0xA5;
    data[index++]=0;	//lenght
    data[index++]=0;	//lenght
    data[index++]=MSG_CODE;
    data[index++]=0;	//src id
    data[index++]=1;	//dest id

    data[index++]=0;	//zero payload
    data[index++]=0;	//zero payload

    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}
/***************************************************************************/
uint8_t prepareData_Temp(uint8_t *data, uint8_t MSG_CODE, uint8_t *temp)
{
    uint8_t index = 0;
    uint16_t crc;
    data[index++]=0xA5;
    data[index++]=0;	//lenght
    data[index++]=0;	//lenght
    data[index++]=MSG_CODE;
    data[index++]=0;	//src id
    data[index++]=1;	//dest id

    copyToArray(data+index,temp,4); //4 byte of temp
    index+=4;

    crc=calcCheckSum(data+3,index-3);
    data[1]=index-3;
    data[2]=(index-3)>>8;
    data[index++]=crc;
    data[index++]=crc>>8;
    data[index++]=0x0D;
    return index;
}
/*************************************************************************/
/********************Check user and password*******************/
bool Check_User_Password(uint8_t *array_user, uint8_t *array_password)
{
	uint32_t user = 0;
	uint32_t password = 0;
	uint32_t user_password[5]={0};
	uint8_t Number_User = 0;


	user = array_user[0] | array_user[1]<<8 | array_user[2]<<16 | array_user[3]<<24;
	password = array_password[0] | array_password[1]<<8 | array_password[2]<<16 | array_password[3]<<24;

	Number_User =  Load_All_User(user_password);
	int i =0;
	for(i=0; i<Number_User; i++)
	{
		if((user == user_password[2*i]) && (password == user_password[2*i+1]))
			return true;
	}
	return false;
}
