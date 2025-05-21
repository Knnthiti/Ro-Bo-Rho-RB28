/*
 * Encoder.h
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */

#ifndef ENCODER_MOTOR_H_
#define ENCODER_MOTOR_H_

#include "stdint.h"
#include "stdlib.h"

#include "math.h"
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

typedef enum{
	_LF = 0,
	_LB = 1,
	_RF = 2,
	_RB = 3,
	_EXTRA1 = 4,
	_EXTRA2 = 5
}motor_Wheel;

extern motor_Wheel _Wheel;

typedef struct{
	int16_t _Count[6]; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
	float _RPM[6];     //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
	float _PID[6];     //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
}Motor_feedback;

extern Motor_feedback _Motor;

void Motor_setup_LF(TIM_HandleTypeDef *_TIM_14_CH1 ,TIM_HandleTypeDef *_TIM_5  ,char* _IN_LF);
void Motor_setup_LB(TIM_HandleTypeDef *_TIM_15_CH1 ,TIM_HandleTypeDef *_TIM_1  ,char* _IN_LB);
void Motor_setup_RF(TIM_HandleTypeDef *_TIM_11_CH1 ,TIM_HandleTypeDef *_TIM_8  ,char* _IN_RF);
void Motor_setup_RB(TIM_HandleTypeDef *_TIM_12_CH2 ,TIM_HandleTypeDef *_TIM_4  ,char* _IN_RB);
void Motor_setup_EXTRA1(TIM_HandleTypeDef *_TIM_9_CH1     ,TIM_HandleTypeDef *_TIM_2  ,char* _IN_EXTRA1);
void Motor_setup_EXTRA2(TIM_HandleTypeDef *_TIM_10_CH1    ,TIM_HandleTypeDef *_TIM_3  ,char* _IN_EXTRA2);

void Motor_DutyCycle_LF(int16_t DutyCycle_LF);
void Motor_DutyCycle_LB(int16_t DutyCycle_LB);
void Motor_DutyCycle_RF(int16_t DutyCycle_RF);
void Motor_DutyCycle_RB(int16_t DutyCycle_RB);
void Motor_DutyCycle_EXTRA1(int16_t DutyCycle_EXTRA1);
void Motor_DutyCycle_EXTRA2(int16_t DutyCycle_EXTRA2);


typedef struct{
	uint16_t _freq;
	uint16_t CPR;
	uint16_t Gear_Ratio;
}Setup_Speed_Motor;

extern Setup_Speed_Motor _Setup;

void Setup_CPR(uint16_t CPR);

void Setup_Gear_Ratio(uint16_t _Gear_Ratio);

void Setup_frequency_Motor(uint16_t freq);

int16_t getCount(TIM_HandleTypeDef *TIM ,motor_Wheel _Wheel);

float getRPM_TIM_Wheel(TIM_HandleTypeDef *TIM ,motor_Wheel _Wheel);

float getRPM_to_Rad_s(float RPM);
float getRad_s_to_RPM(float Rad_s);



void Setup_PID_Wheel(float Kp ,float Ki ,float Kd ,float _min_speed ,float _max_speed ,motor_Wheel _Wheel);

float PID_Speed(float _Setpoint ,float RPM ,motor_Wheel _Wheel);

float Motor_Speed_LF(int16_t RPM_INPUT ,float _RPM_LF);
float Motor_Speed_LB(int16_t RPM_INPUT ,float _RPM_LB);
float Motor_Speed_RF(int16_t RPM_INPUT ,float _RPM_RF);
float Motor_Speed_RB(int16_t RPM_INPUT ,float _RPM_RB);
float Motor_Speed_EXTRA1(int16_t RPM_INPUT ,float RPM_EXTRA1);
float Motor_Speed_EXTRA2(int16_t RPM_INPUT ,float RPM_EXTRA2);

void digitalWrite(char* _PIN, uint8_t vlue);

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);
#endif /* ENCODER_MOTOR_H_ */
