/*
 * mpu6050.h
 *
 *  Created on: Oct 29, 2015
 *      Author: Bach
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#ifndef __i2c_h__
#define __i2c_h__

#ifdef __cplusplus
extern "C" {
#endif

#define MPU6050_SMPLRT_DIV                  0x19
#define MPU6050_INT_PIN_CFG                 0x37
#define MPU6050_ACCEL_XOUT_H                0x3B
#define MPU6050_GYRO_XOUT_H                 0x43
#define MPU6050_PWR_MGMT_1                  0x6B
#define MPU6050_WHO_AM_I                    0x75

#define MPU6050_ADDRESS                     0x68
#define MPU6050_WHO_AM_I_ID                 0x68

// Scale factor for +-1000deg/s and +-8g - see datasheet:
#define MPU6050_GYRO_SCALE_FACTOR_1000      32.8f
#define MPU6050_ACC_SCALE_FACTOR_8          4096.0f

#define rad_to_degree						57.295779

void initI2C(void);
void i2cWrite(uint8_t addr, uint8_t regAddr, uint8_t data);
void i2cWriteData(uint8_t addr, uint8_t regAddr, uint8_t *date, uint8_t length);
uint8_t i2cRead(uint8_t addr, uint8_t regAddr);
void i2cReadData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length);
void initMPU6050(void);
void getMPU6050Data(void);

void Inc_ACC();
void Inc_GYRO();
void Calibrate_MPU6050();
void Get_Zero_Angle();

float MPU6050_Get_X_angle();
float MPU6050_Get_Y_angle();

float MPU6050_Gyro_X_rate();
float MPU6050_Gyro_Y_rate();

#ifdef __cplusplus
}
#endif

#endif



#endif /* MPU6050_H_ */
