/*
 * mpu6050.c
 *
 *  Created on: Oct 29, 2015
 *      Author: Bach
 */
#include "include.h"

int16_t accaxisX,accaxisY,accaxisZ;
int16_t gyroaxisX,gyroaxisY,gyroaxisZ;

int16_t accaxisX_offset = 0;
int16_t accaxisY_offset = 0;
int16_t accaxisZ_offset = 0;

int16_t gyroaxisX_zero = 0;
int16_t gyroaxisY_zero = 0;
int16_t gyroaxisZ_zero = 0;

int32_t int32_accaxisX=0, int32_accaxisY=0, int32_accaxisZ=0;
int32_t int32_gyroaxisX=0, int32_gyroaxisY=0 ,int32_gyroaxisZ=0;


extern float AngleX_Zero, AngleY_Zero;

/*
 * Initial I2C1
 */
void initI2C(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1); 		// Enable I2C1 peripheral
    SysCtlDelay(2); 									// Insert a few cycles after enabling the peripheral to allow the clock
    													// to be fully activated

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); 		// Enable GPIOA peripheral
    SysCtlDelay(2); 									// Insert a few cycles after enabling the peripheral to allow the clock
    													// to be fully activated


    													// Use alternate function
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6); 	// Use pin with I2C SCL peripheral
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7); 		// Use pin with I2C peripheral


    I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(), true); // Enable and set frequency to 400 kHz if 3rd parameter is true(100KHz if false)

    SysCtlDelay(2); 									// Insert a few cycles after enabling the I2C to allow the clock
    													// to be fully activated
}
/*********************************************************/
/*
 * Bref: write one byte from master to slaver
 * Input parameter:
 * 		1. uint8_t addr : Slaver address
 * 		2. uint8_t regAddr: Slaver register address to write data
 * 		3. uint8_t data: Data will be write
 * Output parameter: None
 * Return: None
 * Notes:
 */
void i2cWrite(uint8_t addr, uint8_t regAddr, uint8_t data)
{
    i2cWriteData(addr, regAddr, &data, 1);
}
/*************************************************************/
/*
 * Bref: write some bytes from master to slaver
 * Input parameter:
 * 		1. uint8_t addr : Slaver address
 * 		2. uint8_t regAddr: Slaver register address to write data
 * 		3. uint8_t *data: pointer to data will be write
 * 		4. uint8_t lenght: the number of byte to be write
 * Output parameter: None
 * Return: None
 * Notes:
 */
void i2cWriteData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(I2C1_BASE, regAddr); // Place address into data register
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START); // Send start condition
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
    uint8_t i = 0;
    for (i = 0; i < length - 1; i++)
    {
        I2CMasterDataPut(I2C1_BASE, data[i]); // Place data into data register
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // Send continues condition
        while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
    }

    I2CMasterDataPut(I2C1_BASE, data[length - 1]); // Place data into data register
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // Send finish condition
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
}
/*****************************************************************************/
uint8_t i2cRead(uint8_t addr, uint8_t regAddr)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(I2C1_BASE, regAddr); // Place address into data register
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done

    I2CMasterSlaveAddrSet(I2C1_BASE, addr, true); // Set to read mode

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE); // Tell master to read data
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
    return I2CMasterDataGet(I2C1_BASE); // Read data
}
/**************************************************************************/
void i2cReadData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length)
{
    I2CMasterSlaveAddrSet(I2C1_BASE, addr, false); // Set to write mode

    I2CMasterDataPut(I2C1_BASE, regAddr); // Place address into data register
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done

    I2CMasterSlaveAddrSet(I2C1_BASE, addr, true); // Set to read mode

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START); // Send start condition
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
    data[0] = I2CMasterDataGet(I2C1_BASE); // Place data into data register
    uint8_t i = 1;
    for (i = 1; i < length - 1; i++) {
        I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT); // Send continues condition
        while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
        data[i] = I2CMasterDataGet(I2C1_BASE); // Place data into data register
    }

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH); // Send finish condition
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
    data[length - 1] = I2CMasterDataGet(I2C1_BASE); // Place data into data register
}
/*********************************************************************/
void initMPU6050(void)
{
	uint8_t i2cBuffer[5]; // Buffer for I2C data
	i2cBuffer[0] = i2cRead(MPU6050_ADDRESS, MPU6050_WHO_AM_I);
	i2cWrite(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, (1 << 7)); // Reset device, this resets all internal registers to their default values
	SysCtlDelay(SysCtlClockGet()/100);
	while (i2cRead(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1) & (0x01 << 7))
	{
		LED_RED_ON;
		//Led Red(on) for indicating can not connect to MPU6050
		// Wait for the bit to clear
	};

	SysCtlDelay(SysCtlClockGet()/100);
	i2cWrite(MPU6050_ADDRESS, MPU6050_PWR_MGMT_1, (1 << 3) | (1 << 0)); // Disable sleep mode, disable temperature sensor and use PLL as clock reference

	i2cBuffer[0] = 0; // Set the sample rate to 1kHz - 1kHz/(1+0) = 1kHz
	i2cBuffer[1] = 0x03; // Disable FSYNC and set 41 Hz Gyro filtering, 1 KHz sampling
	i2cBuffer[2] = 2 << 3; // Set Gyro Full Scale Range to +-1000deg/s
	i2cBuffer[3] = 2 << 3; // Set Accelerometer Full Scale Range to +-8g
	i2cBuffer[4] = 0x03; // 41 Hz Acc filtering
	i2cWriteData(MPU6050_ADDRESS, MPU6050_SMPLRT_DIV, i2cBuffer, 5); // Write to all five registers at once


	/* Enable Raw Data Ready Interrupt on INT pin */
	i2cBuffer[0] = (1 << 5) | (1 << 4); // Enable LATCH_INT_EN and INT_ANYRD_2CLEAR
	// When this bit is equal to 1, the INT pin is held high until the interrupt is cleared
	// When this bit is equal to 1, interrupt status is cleared if any read operation is performed
	i2cBuffer[1] = (1 << 0);            // Enable RAW_RDY_EN - When set to 1, Enable Raw Sensor Data Ready interrupt to propagate to interrupt pin
	i2cWriteData(MPU6050_ADDRESS, MPU6050_INT_PIN_CFG, i2cBuffer, 2); // Write to both registers at once
}
/**********************************************************************/
void getMPU6050Data(void)
{
	uint8_t buf[14];
	i2cReadData(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, buf, 14); // Note that we can't write directly into MPU6050_t
																 // because of endian conflict. So it has to be done manually

	accaxisX = (int16_t)((buf[0] << 8) | buf[1]);
	accaxisY = (int16_t)((buf[2] << 8) | buf[3]);
	accaxisZ = (int16_t)((buf[4] << 8) | buf[5]);

	gyroaxisX = (int16_t)((buf[8] << 8) | buf[9]) - gyroaxisX_zero;
	gyroaxisY = (int16_t)((buf[10] << 8) | buf[11]) - gyroaxisY_zero;
	gyroaxisZ = (int16_t)((buf[12] << 8) | buf[13]) - gyroaxisZ_zero;
}
/*********************************************************************/
void Inc_ACC()
{
	int32_accaxisX += accaxisX;
	int32_accaxisY += accaxisY;
	int32_accaxisZ += accaxisZ;
}
/*********************************************************************/
void Inc_GYRO()
{
	int32_gyroaxisX += gyroaxisX;
	int32_gyroaxisY += gyroaxisY;
	int32_gyroaxisZ += gyroaxisZ;
}
/*********************************************************************/
/*
 *
 */
void Calibrate_MPU6050()
{

	int32_t accaxisX_offset1000=0;
	int32_t accaxisY_offset1000=0;
	int32_t accaxisZ_offset1000=0;

	int32_t gyroaxisX_zero1000=0;
	int32_t gyroaxisY_zero1000=0;
	int32_t gyroaxisZ_zero1000=0;

	uint32_t i  = 0;
	for(i = 0; i<1000; i++)
	{
		uint8_t buf[14];
		i2cReadData(MPU6050_ADDRESS, MPU6050_ACCEL_XOUT_H, buf, 14); 	// Note that we can't write directly into MPU6050_t
																		 // because of endian conflict. So it has to be done manually

//		accaxisX_offset1000 += (int16_t)(buf[0] << 8) | buf[1];
//		accaxisY_offset1000 += (int16_t)(buf[2] << 8) | buf[3];
//		accaxisZ_offset1000 += (int16_t)(buf[4] << 8) | buf[5];

		gyroaxisX_zero1000 += (int16_t)(buf[8] << 8) | buf[9];
		gyroaxisY_zero1000 += (int16_t)(buf[10] << 8) | buf[11];
		gyroaxisZ_zero1000 += (int16_t)(buf[12] << 8) | buf[13];

		SysCtlDelay(SysCtlClockGet()/3000);
	}

//	accaxisX_offset = accaxisX_offset1000/1000;
//	accaxisY_offset = accaxisY_offset1000/1000;
//	accaxisZ_offset = accaxisZ_offset1000/1000;

	gyroaxisX_zero = gyroaxisX_zero1000/1000;
	gyroaxisY_zero = gyroaxisY_zero1000/1000;
	gyroaxisZ_zero = gyroaxisZ_zero1000/1000;

#ifdef _DEBUG_CALIB_

	UARTPuts(UART0_BASE,"Calib MPU6050:\n");

	UARTPuts(UART0_BASE,"accaxisX_offest:\t");
	UARTPutn(UART0_BASE,accaxisX);
	UARTPuts(UART0_BASE,"\n");

	UARTPuts(UART0_BASE,"accaxisY_offest:\t");
	UARTPutn(UART0_BASE,accaxisY);
	UARTPuts(UART0_BASE,"\n");

	UARTPuts(UART0_BASE,"accaxisZ_offest:\t");
	UARTPutn(UART0_BASE,accaxisZ);
	UARTPuts(UART0_BASE,"\n");

	UARTPuts(UART0_BASE,"gyroaxisX_zero:\t");
	UARTPutn(UART0_BASE,gyroaxisX_zero);
	UARTPuts(UART0_BASE,"\n");

	UARTPuts(UART0_BASE,"gyroaxisY_zero:\t");
	UARTPutn(UART0_BASE,gyroaxisY_zero);
	UARTPuts(UART0_BASE,"\n");

	UARTPuts(UART0_BASE,"gyroaxisZ_zero:\t");
	UARTPutn(UART0_BASE,gyroaxisZ_zero);
	UARTPuts(UART0_BASE,"\n");
#endif
}
/*******************************************************************/
void Get_Zero_Angle()
{

	double AngleX_Zero500=0;
	double AngleY_Zero500=0;

	uint32_t i  = 0;
		for(i = 0; i<500; i++)
		{
			getMPU6050Data();
			AngleX_Zero500 += MPU6050_Get_X_angle();
			AngleY_Zero500 += MPU6050_Get_Y_angle();

			SysCtlDelay(SysCtlClockGet()/3000);
		}
		AngleX_Zero = AngleX_Zero500/500;
		AngleY_Zero = AngleY_Zero500/500;
}
/********************************************************************/
/*
 *
 */
float MPU6050_Get_X_angle()
{
	float acc_x_angle = 0;
	acc_x_angle=(rad_to_degree)*atan2((float)accaxisY, sqrt((float)(accaxisX*accaxisX)+(float)(accaxisZ*accaxisZ)));
	return acc_x_angle;
}

float MPU6050_Get_Y_angle()
{
	float acc_y_angle = 0;
	acc_y_angle=(rad_to_degree)*atan2((float)(-accaxisX), sqrt((float)(accaxisY*accaxisY)+(float)(accaxisZ*accaxisZ)));
	return acc_y_angle;
}
/*********************************************************************/
float MPU6050_Gyro_X_rate()
{
	float gyro_x_rate = 0;
	gyro_x_rate = (float)(gyroaxisX)/MPU6050_GYRO_SCALE_FACTOR_1000;
	return gyro_x_rate;
}

float MPU6050_Gyro_Y_rate()
{
	float gyro_y_rate = 0;
	gyro_y_rate = (float)(gyroaxisY)/MPU6050_GYRO_SCALE_FACTOR_1000;
	return gyro_y_rate;
}

