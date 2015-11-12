/*
 * EEPROM.c
 *
 *  Created on: Aug 6, 2013
 *      Author: Admin
 */
#include "../include.h"
#include "driverlib/eeprom.h"

typedef enum
{
	EEPROM_MSG_INVALID_ADDRESS = 0,
	EEPROM_MSG_INVALID_NUMOFWORDS,
	EEPROM_MSG_OK
} EEPROM_MSG;

static EEPROM_MSG EEPROMWrite(uint32_t *pui32_Data, uint32_t ui32WordAddress, uint32_t NumOfWords);
static EEPROM_MSG EEPROMReadWords(uint32_t *pui32_Data, uint32_t ui32WordAddress, uint32_t NumOfWords);

static EEPROM_MSG EEPROMWrite(uint32_t *pui32_Data, uint32_t ui32WordAddress, uint32_t NumOfWords)
{
	uint32_t Address;
	if (ui32WordAddress > 0x7ff)
	{
		return (EEPROM_MSG_INVALID_ADDRESS);
	}
	if ((ui32WordAddress + NumOfWords) > 0x7ff)
	{
		return (EEPROM_MSG_INVALID_NUMOFWORDS);
	}
	Address = ui32WordAddress << 2;
	ROM_EEPROMProgram(pui32_Data, Address, NumOfWords << 2);

	return EEPROM_MSG_OK;
}

static EEPROM_MSG EEPROMReadWords(uint32_t *pui32_Data, uint32_t ui32WordAddress, uint32_t NumOfWords)
{
	uint32_t Address;
	if (ui32WordAddress > 0x7ff)
	{
		return (EEPROM_MSG_INVALID_ADDRESS);
	}
	if ((ui32WordAddress + NumOfWords) > 0x7ff)
	{
		return (EEPROM_MSG_INVALID_NUMOFWORDS);
	}
	Address = ui32WordAddress << 2;
	ROM_EEPROMRead(pui32_Data, Address, NumOfWords << 2);

	return EEPROM_MSG_OK;
}
void EEPROMConfig()
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);	//Enable EEPROM
	EEPROMInit();
}
void saveMotorModel()
{
	real_T Theta[4];
	int32_t intTheta[4];
	speed_GetMotorModel(MOTOR_Left,Theta);
	intTheta[0]=(int32_t)(Theta[0]*1e6);
	intTheta[1]=(int32_t)(Theta[1]*1e6);
	intTheta[2]=(int32_t)(Theta[2]*1e6);
	intTheta[3]=(int32_t)(Theta[3]*1e6);
	EEPROMWrite(intTheta, 0x10, 4);

	speed_GetMotorModel(MOTOR_Right,Theta);
	intTheta[0]=(int32_t)(Theta[0]*1e6);
	intTheta[1]=(int32_t)(Theta[1]*1e6);
	intTheta[2]=(int32_t)(Theta[2]*1e6);
	intTheta[3]=(int32_t)(Theta[3]*1e6);
	EEPROMWrite(intTheta, 0x20, 4);
}
void loadMotorModel()
{
	real_T Theta[4];
	int32_t intTheta[4]={0};
	EEPROMReadWords(intTheta, 0x10, 4);
	Theta[0]=((real_T)intTheta[0])*1e-6;
	Theta[1]=((real_T)intTheta[1])*1e-6;
	Theta[2]=((real_T)intTheta[2])*1e-6;
	Theta[3]=((real_T)intTheta[3])*1e-6;
	speed_SetMotorModel(MOTOR_Left,Theta);

	EEPROMReadWords(intTheta, 0x20, 4);
	Theta[0]=((real_T)intTheta[0])*1e-6;
	Theta[1]=((real_T)intTheta[1])*1e-6;
	Theta[2]=((real_T)intTheta[2])*1e-6;
	Theta[3]=((real_T)intTheta[3])*1e-6;
	speed_SetMotorModel(MOTOR_Right,Theta);
}
/***********************************************************/
void Save_User(uint8_t *user, uint8_t *password)
{
	uint32_t data_info=0;
	uint32_t data_user_password[2]={0};

	EEPROMReadWords(data_info, User_Password_EEPROM, 1);

	data_user_password[0] = *user | (*user+1)<<8 | (*user+2)<<16 | (*user+3)<<24;
	data_user_password[1] = *password | (*password+1)<<8 | (*password+2)<<16 | (*password+3)<<24;
	EEPROMWrite(data_user_password, User_Password_EEPROM+1 + data_info*2 , 2);

	data_info++;
	if(data_info >5) data_info = 5;
	EEPROMWrite(data_info, User_Password_EEPROM, 1);
}
/**************************************************************/
uint8_t Load_All_User(uint32_t *user_password)
{
	uint32_t data_info=0;
	EEPROMReadWords(data_info, User_Password_EEPROM, 1);

	EEPROMReadWords(user_password, User_Password_EEPROM+1, data_info);
	return data_info;
}
