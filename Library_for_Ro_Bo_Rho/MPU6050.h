/*
 * MPU6050.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "stdint.h"
#include "stm32G0xx_hal.h"

#include "MPU6050.h"

#define MPU6050_ADDR 0x68<<1   // address I2C is MPU6050

#define power_management 0x6B
#define DATA_RATE 0x19

#define ACCEL_CONFIG_REG 0x1C
#define GYRO_CONFIG_REG 0x1B

#define GYRO_XOUT_H 0x43

#define Degree_to_Radian 0.017453f

uint8_t Scan_I2C(I2C_HandleTypeDef *I2Cinstance);

void Setup_MPU6050(I2C_HandleTypeDef *I2Cinstance ,uint8_t PWR_MGMT_1 ,uint8_t SMPLRT_DIV);

void MPU6050_calib();

extern int16_t gx;
extern int16_t gy;
extern int16_t gz;

void ReadMPU6050();

int16_t get_gx();
int16_t get_gy();
int16_t get_gz();

extern float DegreeZ;
float getDegreeZ();

extern float RadianZ;
float getRadianZ();

#endif /* MPU6050_H_ */
