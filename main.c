#include "include.h"


#define _DEBUG_MORTOR_

/*
 * main.c
 */
extern int16_t accaxisX,accaxisY,accaxisZ;
extern int16_t gyroaxisX,gyroaxisY,gyroaxisZ;

extern int32_t int32_accaxisX, int32_accaxisY, int32_accaxisZ;
extern int32_t int32_gyroaxisX, int32_gyroaxisY,int32_gyroaxisZ;

extern int16_t accaxisX_offset,accaxisY_offset,accaxisZ_offset;
extern int16_t gyroaxisX_zero,gyroaxisY_zero,gyroaxisZ_zero;


extern bool bool_Process_Flag;

float X_angle = 0.0, Y_angle = 0.0;			 // using float or double?????

float Acc_X_angle = 0.0, Acc_Y_angle = 0.0;
float Gyro_X_rate = 0.0, Gyro_Y_rate = 0.0;

float AngleX_Zero = 0, AngleY_Zero = 0;

static uint8_t MPU_Step = 0;
static uint32_t ms_StartLoop = 0;
float dt = 0.0;
int32_t int32_Control_Signal = 0;

extern PID_PARAMETERS PID_Small_Angle;
extern PID_PARAMETERS PID_Big_Angle;
bool PID_Process_Flag = false;
int8_t Pre_Sig = 1;
float Target_Position = 0.0;

int32_t Saturation_Left_PWM = 0;
int32_t Saturation_Right_PWM = 0;

const float Left_Factor = 1.0;
const float Right_Factor  = 1.0;

void Process_Balancing_Complementary_Filter();
void Process_Balancing_2nd_Complementary_Filter();
void Process_Balancing_Kalman_Filter();
int8_t Check_Postive_Sig(double Data);

/*********************************************************************/
/*
 *
 */
void main(void)
{
	Config_System();

	Config_PWM();
	SysCtlDelay(SysCtlClockGet()/300);
	DISSABLE_PWM();
	LED_GREEN_OFF;				// LED_GREEN(OFF) : Dissable PWM

	UART0_init();
	Timer1Init();
	initI2C();
	SysCtlDelay(SysCtlClockGet()/300);

	UARTPuts(UART0_BASE,"Initial MPU6050 :\n");
	initMPU6050();
	LED_RED_OFF;
	SysCtlDelay(SysCtlClockGet()/300);
	UARTPuts(UART0_BASE,"Initial MPU6050 : OK \n");

	UARTPuts(UART0_BASE,"Calib MPU6050 :\n");
	Calibrate_MPU6050();
	UARTPuts(UART0_BASE,"Calib MPU6050 : OK \n");

	UARTPuts(UART0_BASE,"Get_Zero_Angle :\n");
	Get_Zero_Angle();
	UARTPuts(UART0_BASE,"Get_Zero_Angle : OK \n");

	IntMasterEnable(); 			//enable processor interrupts

	ENABLE_PWM();
	while(1)
	{
		Togle(LED_RED,100);			// Togle LED_RED: 100 * 10ms = 1s. setup: DONE, Running Process_Balancing();

#ifdef _USE_COMPLEMENTARY_FILTER_
		Process_Balancing_Complementary_Filter();
#endif

#ifdef _USE_2ND_COMPLEMENTARY_FILTER_
		Process_Balancing_2nd_Complementary_Filter();
#endif

#ifdef _USE_KALMAN_FILTER_
		Process_Balancing_Kalman_Filter();
#endif

		Target_Position = 0.0;
//		Y_angle = Y_angle - AngleY_Zero;
		if(PID_Process_Flag == true)
		{
			PID_Process_Flag = false;
			/******************************Small_Angle*********************************/
			if(((int)(Y_angle - Target_Position) < 3) && ((int)(Y_angle + Target_Position) > -3))
			{
				int32_Control_Signal =  (int32_t)(pid_process(&PID_Small_Angle, Y_angle, Target_Position));
				
				Saturation_Left_PWM = 75;
				Saturation_Right_PWM = 75;

				if(Check_Postive_Sig(int32_Control_Signal) != Pre_Sig)
				{
					Pre_Sig = Check_Postive_Sig(int32_Control_Signal);
					pid_reset(&PID_Small_Angle);
//					int32_Control_Signal = 0;
				}
			}
			/*************************Saturation_Angle(+)****************************/
			else if((int)(Y_angle - Target_Position) > 10)
			{
				int32_Control_Signal = -90;
				Saturation_Left_PWM = 90;
				Saturation_Right_PWM = 90;
			}
			/*************************Saturation_Angle(-)****************************/
			else if((int)(Y_angle + Target_Position) < -10)
			{
				int32_Control_Signal = 90;
				Saturation_Left_PWM = 90;
				Saturation_Right_PWM = 90;
			}
			/******************************Big_Angle*********************************/			
			else
			{
				int32_Control_Signal =  (int32_t)(pid_process(&PID_Big_Angle, Y_angle, Target_Position));
				Saturation_Left_PWM = 90;
				Saturation_Right_PWM = 90;

				if(Check_Postive_Sig(int32_Control_Signal) != Pre_Sig)
				{
					Pre_Sig = Check_Postive_Sig(int32_Control_Signal);
					pid_reset(&PID_Big_Angle);
//					int32_Control_Signal = 0;
				}
			}

			SetPWM_MotorLeft(int32_Control_Signal,Left_Factor, Saturation_Left_PWM);
			SetPWM_MotorRight(int32_Control_Signal,Right_Factor, Saturation_Right_PWM);
		}
		
			UARTPutn(UART0_BASE,Y_angle);
			UARTPuts(UART0_BASE," do\n");

			UARTPutn(UART0_BASE,int32_Control_Signal);
			UARTPuts(UART0_BASE,"... \n");
	/*----------------------Set PWM()--------------------------*/
	}
}
/*******************************************************************************/
/*
 *
 */
void Process_Balancing_Complementary_Filter(void)
{
	if(bool_Process_Flag == true)
	{
		bool_Process_Flag = false;
		MPU_Step %=10;
		switch(MPU_Step)
		{
		case 0: //MPU_Step++;break;
		case 1: //MPU_Step++;break;
		case 2: //MPU_Step++;break;
		case 3: //MPU_Step++;break;
		case 4: //MPU_Step++;break;
		case 5: //MPU_Step++;break;
		case 6: //MPU_Step++;break;
		case 7: //MPU_Step++;break;
		case 8:
			getMPU6050Data();
			Inc_ACC();
			Inc_GYRO();
			MPU_Step++;
		break;
		case 9:
			accaxisX = (int16_t)((int32_accaxisX/MPU_Step));
			accaxisY = (int16_t)((int32_accaxisY/MPU_Step));
			accaxisZ = (int16_t)((int32_accaxisZ/MPU_Step));

//			gyroaxisX = (int16_t)((int32_gyroaxisX/MPU_Step));
			gyroaxisY = (int16_t)((int32_gyroaxisY/MPU_Step));
//			gyroaxisZ = (int16_t)((int32_gyroaxisZ/MPU_Step));

//			Acc_X_angle = MPU6050_Get_X_angle();
			Acc_Y_angle = MPU6050_Get_Y_angle();

//			Gyro_X_rate = MPU6050_Gyro_X_rate();
			Gyro_Y_rate = MPU6050_Gyro_Y_rate();

			int32_accaxisX=0;
			int32_accaxisY=0;
			int32_accaxisZ=0;

			int32_gyroaxisX=0;
			int32_gyroaxisY=0;
			int32_gyroaxisZ=0;


			dt = ((float)(Get_tick() - ms_StartLoop))/(1000.00);
			ms_StartLoop = Get_tick();

//			X_angle = Complementary_X_Filter(dt);
			Y_angle = Complementary_Y_Filter(dt);


//			X_angle = Second_order_Complementary_X_Filter(dt);
//			Y_angle = Second_order_Complementary_Y_Filter(dt);

//			X_angle = Kalman_X_Filter(Acc_X_angle, Gyro_X_rate, dt);
//			Y_angle = Kalman_Y_Filter(Acc_Y_angle, Gyro_Y_rate, dt);

			MPU_Step=10;
		break;
		}

	}
}

/*******************************************************************************/
/*
 *
 */
void Process_Balancing_2nd_Complementary_Filter(void)
{
	if(bool_Process_Flag == true)
	{
		bool_Process_Flag = false;
		MPU_Step %=10;
		switch(MPU_Step)
		{
		case 0: //MPU_Step++;break;
		case 1: //MPU_Step++;break;
		case 2: //MPU_Step++;break;
		case 3: //MPU_Step++;break;
		case 4: //MPU_Step++;break;
		case 5: //MPU_Step++;break;
		case 6: //MPU_Step++;break;
		case 7: //MPU_Step++;break;
		case 8:
			getMPU6050Data();
			Inc_ACC();
			Inc_GYRO();
			MPU_Step++;
		break;
		case 9:
			accaxisX = (int16_t)((int32_accaxisX/MPU_Step));
			accaxisY = (int16_t)((int32_accaxisY/MPU_Step));
			accaxisZ = (int16_t)((int32_accaxisZ/MPU_Step));

//			gyroaxisX = (int16_t)((int32_gyroaxisX/MPU_Step));
			gyroaxisY = (int16_t)((int32_gyroaxisY/MPU_Step));
//			gyroaxisZ = (int16_t)((int32_gyroaxisZ/MPU_Step));

//			Acc_X_angle = MPU6050_Get_X_angle();
			Acc_Y_angle = MPU6050_Get_Y_angle();

//			Gyro_X_rate = MPU6050_Gyro_X_rate();
			Gyro_Y_rate = MPU6050_Gyro_Y_rate();

			int32_accaxisX=0;
			int32_accaxisY=0;
			int32_accaxisZ=0;

			int32_gyroaxisX=0;
			int32_gyroaxisY=0;
			int32_gyroaxisZ=0;


			dt = ((float)(Get_tick() - ms_StartLoop))/(1000.00);
			ms_StartLoop = Get_tick();

//			X_angle = Complementary_X_Filter(dt);
//			Y_angle = Complementary_Y_Filter(dt);


//			X_angle = Second_order_Complementary_X_Filter(dt);
			Y_angle = Second_order_Complementary_Y_Filter(dt);

//			X_angle = Kalman_X_Filter(Acc_X_angle, Gyro_X_rate, dt);
//			Y_angle = Kalman_Y_Filter(Acc_Y_angle, Gyro_Y_rate, dt);

			MPU_Step=10;
		break;
		}

	}
}
/*******************************************************************************/
/*
 *
 */
void Process_Balancing_Kalman_Filter(void)
{
	if(bool_Process_Flag == true)
	{
		bool_Process_Flag = false;
		MPU_Step %=5;
		switch(MPU_Step)
		{
		case 0: //MPU_Step++;break;
		case 1: //MPU_Step++;break;
		case 2: //MPU_Step++;break;
		case 3: //MPU_Step++;break;
			getMPU6050Data();
			Inc_ACC();
			Inc_GYRO();
			MPU_Step++;
		break;
		case 4:
			accaxisX = (int16_t)((int32_accaxisX/MPU_Step));
			accaxisY = (int16_t)((int32_accaxisY/MPU_Step));
			accaxisZ = (int16_t)((int32_accaxisZ/MPU_Step));

//			gyroaxisX = (int16_t)((int32_gyroaxisX/MPU_Step));
			gyroaxisY = (int16_t)((int32_gyroaxisY/MPU_Step));
//			gyroaxisZ = (int16_t)((int32_gyroaxisZ/MPU_Step));

//			Acc_X_angle = MPU6050_Get_X_angle();
			Acc_Y_angle = MPU6050_Get_Y_angle();

//			Gyro_X_rate = MPU6050_Gyro_X_rate();
			Gyro_Y_rate = MPU6050_Gyro_Y_rate();

			int32_accaxisX=0;
			int32_accaxisY=0;
			int32_accaxisZ=0;

			int32_gyroaxisX=0;
			int32_gyroaxisY=0;
			int32_gyroaxisZ=0;


			dt = ((float)(Get_tick() - ms_StartLoop))/(1000.00);
			ms_StartLoop = Get_tick();

//			X_angle = Complementary_X_Filter(dt);
//			Y_angle = Complementary_Y_Filter(dt);


//			X_angle = Second_order_Complementary_X_Filter(dt);
//			Y_angle = Second_order_Complementary_Y_Filter(dt);

//			X_angle = Kalman_X_Filter(Acc_X_angle, Gyro_X_rate, dt);
			Y_angle = Kalman_Y_Filter(Acc_Y_angle, Gyro_Y_rate, dt);

			MPU_Step++;
		break;
		}

	}
}
/******************************************************************************/
int8_t Check_Postive_Sig(double Data)
{
	if(Data > 0) return (1);
	return (-1);
}
//*****************************************************************************
//
//! Uart0 interrupt
//
//*****************************************************************************
void UART0IntHandler(void)
{

}
