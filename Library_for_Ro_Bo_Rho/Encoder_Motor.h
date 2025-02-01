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
#include "stm32G0xx_hal.h"

#define LF 0
#define LB 1
#define RF 2
#define RB 3

// Encoder_Mode STM32G071RB is 4 TIMER
void Motor_setup_LF(TIM_HandleTypeDef *TIM_15_CH2 ,TIM_HandleTypeDef *TIM_1   ,int8_t Rotate_LF ,char* IN1_LF ,char* IN2_LF);
void Motor_setup_LB(TIM_HandleTypeDef *TIM_15_CH1 ,TIM_HandleTypeDef *TIM_3   ,int8_t Rotate_LB ,char* IN1_LF ,char* IN2_LF);
void Motor_setup_RF(TIM_HandleTypeDef *TIM_14     ,TIM_HandleTypeDef *TIM_2   ,int8_t Rotate_RF ,char* IN1_LF ,char* IN2_LF);
void Motor_setup_RB_LPTIM(TIM_HandleTypeDef *TIM_16     ,LPTIM_HandleTypeDef *LPTIM ,int8_t Rotate_RB  ,char* IN1_LF ,char* IN2_LF);

void Setup_CPR(float CPR);
void Setup_Gear_Ratio(float _Gear_Ratio);

void Motor_DutyCycle_LF(int16_t DutyCycle_LF);
void Motor_DutyCycle_LB(int16_t DutyCycle_LB);
void Motor_DutyCycle_RF(int16_t DutyCycle_RF);
void Motor_DutyCycle_RB(int16_t DutyCycle_RB);

void Setup_frequency_Motor(uint8_t freq);

int16_t getCount(TIM_HandleTypeDef *TIM);
float getRPM_TIM_Wheel(TIM_HandleTypeDef *TIM ,uint8_t _Wheel);

int16_t getCount_LPTIM(LPTIM_HandleTypeDef *LPTIM);
float getRPM_LPTIM_Wheel(LPTIM_HandleTypeDef *LPTIM ,uint8_t _Wheel);

float getRPM_to_Rad_s(float RPM);
float getRad_s_to_RPM(float Rad_s);

void Setup_PID_LF(float Kp_LF ,float Ki_LF ,float Kd_LF ,float min_speed_LF ,float max_speed_LF);
void Setup_PID_LB(float Kp_LB ,float Ki_LB ,float Kd_LB ,float min_speed_LB ,float max_speed_LB);
void Setup_PID_RF(float Kp_RF ,float Ki_RF ,float Kd_RF ,float min_speed_RF ,float max_speed_RF);
void Setup_PID_RB(float Kp_RB ,float Ki_RB ,float Kd_RB ,float min_speed_RB ,float max_speed_RB);

float PID_Speed(float Setpoint ,uint8_t Wheel);

float Motor_Speed_LF(int16_t _RPM_LF);
float Motor_Speed_LB(int16_t _RPM_LB);
float Motor_Speed_RF(int16_t _RPM_RF);
float Motor_Speed_RB(int16_t _RPM_RB);

void digitalWrite(char* _PIN, uint8_t vlue);
#endif /* ENCODER_MOTOR_H_ */
