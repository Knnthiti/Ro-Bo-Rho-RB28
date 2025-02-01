/*
 * Encoder.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */
#include <Encoder_Motor.h>

LPTIM_HandleTypeDef *LPTIM;
TIM_HandleTypeDef *TIM_1;
TIM_HandleTypeDef *TIM_2;
TIM_HandleTypeDef *TIM_3;

TIM_HandleTypeDef *TIM_14;
TIM_HandleTypeDef *TIM_15_CH1;
TIM_HandleTypeDef *TIM_15_CH2;
TIM_HandleTypeDef *TIM_16;

///////////////////////////////////////////////////////////Setup_MOTOR/////////////////////////////////////////////////////

int8_t Rotate[4] = {1 ,1 ,1 ,1}; //LF ,LB ,RF ,RB

char* IN1_LF;
char* IN2_LF;

char* IN1_LB;
char* IN2_LB;

char* IN1_RF;
char* IN2_RF;

char* IN1_RB;
char* IN2_RB;

void Motor_setup_LF(TIM_HandleTypeDef *_TIM_15_CH2 ,TIM_HandleTypeDef *_TIM_1   ,int8_t Rotate_LF ,char* _IN1_LF ,char* _IN2_LF){
	//Motor_setup_LF(PWM_TIM ,Encoder_TIM   ,Rotate_Encoder ,IN1_LF ,IN2_LF);

	TIM_15_CH2 = _TIM_15_CH2;
	TIM_1      = _TIM_1;

	HAL_TIM_PWM_Start(TIM_15_CH2, TIM_CHANNEL_2);       //PWM
	HAL_TIM_Encoder_Start(TIM_1 , TIM_CHANNEL_ALL);     //Encoder

	IN1_LF = _IN1_LF;
	IN2_LF = _IN2_LF;

	Rotate[0] =  Rotate_LF;
}

void Motor_setup_LB(TIM_HandleTypeDef *_TIM_15_CH1 ,TIM_HandleTypeDef *_TIM_3  ,int8_t Rotate_LB  ,char* _IN1_LB ,char* _IN2_LB){
    //Motor_setup_LB(PWM_TIM ,Encoder_TIM   ,Rotate_Encoder ,IN1_LB ,IN2_LB);

	TIM_15_CH1 = _TIM_15_CH1;
	TIM_3      = _TIM_3;

	HAL_TIM_PWM_Start(TIM_15_CH1, TIM_CHANNEL_1);       //PWM
	HAL_TIM_Encoder_Start(TIM_3 , TIM_CHANNEL_ALL);     //Encoder

	IN1_LB = _IN1_LB;
	IN2_LB = _IN2_LB;

	Rotate[1] =  Rotate_LB;
}

void Motor_setup_RF(TIM_HandleTypeDef *_TIM_14     ,TIM_HandleTypeDef *_TIM_2  ,int8_t Rotate_RF  ,char* _IN1_RF ,char* _IN2_RF){
    //Motor_setup_RF(PWM_TIM ,Encoder_TIM   ,Rotate_Encoder ,IN1_RF ,IN2_RF);

	TIM_14 = _TIM_14;
	TIM_2  = _TIM_2;

	HAL_TIM_PWM_Start(TIM_14, TIM_CHANNEL_1);       //PWM
	HAL_TIM_Encoder_Start(TIM_2 , TIM_CHANNEL_ALL);     //Encoder

	IN1_RF = _IN1_RF;
	IN2_RF = _IN2_RF;

	Rotate[2] =  Rotate_RF;
}

void Motor_setup_RB_LPTIM(TIM_HandleTypeDef *_TIM_16     ,LPTIM_HandleTypeDef *_LPTIM ,int8_t Rotate_RB ,char* _IN1_RB ,char* _IN2_RB){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,Rotate_Encoder ,IN1_RB ,IN2_RB);

	TIM_16 = _TIM_16;
	LPTIM  = _LPTIM;

	HAL_TIM_PWM_Start(TIM_16, TIM_CHANNEL_1);       //PWM
	HAL_LPTIM_Encoder_Start(LPTIM, 0xFFFF);         //Encoder

	IN1_RB = _IN1_RB;
	IN2_RB = _IN2_RB;

	Rotate[3] =  Rotate_RB;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////PID///////////////////////////////////////////////////////////////

int16_t getCount(TIM_HandleTypeDef *TIM){
	int16_t count = ((int16_t)(TIM->Instance->CNT));

	return count;
}

int16_t getCount_LPTIM(LPTIM_HandleTypeDef *LPTIM){
	int16_t count = ((int16_t)(LPTIM->Instance->CNT)<<1);

	return count;
}

int16_t Present_Count[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB
int16_t Past_Count[4] = {0 ,0 ,0 ,0};    //LF ,LB ,RF ,RB

uint8_t _freq = 100;

float _RPM[4] = {0 ,0 ,0 ,0}; //Speed   //LF ,LB ,RF ,RB

float CPR = 44.0f;

void Setup_CPR(float _CPR){
	CPR = _CPR;
}

float Gear_Ratio = 48.0f;

void Setup_Gear_Ratio(float _Gear_Ratio){
	Gear_Ratio = _Gear_Ratio;
}

void Setup_frequency_Motor(uint8_t freq){
	_freq = freq;
}

float getRPM_to_Rad_s(float RPM){
	float Rad_s = RPM * 0.10472f;

	return Rad_s;
}

float getRad_s_to_RPM(float Rad_s){
	float RPM__ = Rad_s * 9.549297f;

	return RPM__;
}

float getRPM_TIM_Wheel(TIM_HandleTypeDef *TIM ,uint8_t _Wheel){
	Present_Count[_Wheel] = (int16_t)(getCount(TIM) * Rotate[_Wheel]);

	// V = count/t = count*freq
	_RPM[_Wheel] = (float)((int16_t)(Present_Count[_Wheel] - Past_Count[_Wheel]) * _freq);
	_RPM[_Wheel] = (float)(((_RPM[_Wheel]* 60.0f)/CPR )/Gear_Ratio);

	Past_Count[_Wheel] = Present_Count[_Wheel];

	return _RPM[_Wheel];
}

float getRPM_LPTIM_Wheel(LPTIM_HandleTypeDef *LPTIM ,uint8_t _Wheel){
	Present_Count[_Wheel] = (int16_t)(getCount_LPTIM(LPTIM) * Rotate[_Wheel]);

	// V = count/t = count*freq
	_RPM[_Wheel] = (float)((int16_t)(Present_Count[_Wheel] - Past_Count[_Wheel]) * _freq);
	_RPM[_Wheel] = (float)(((_RPM[_Wheel]* 60.0f)/CPR )/Gear_Ratio);

	Past_Count[_Wheel] = Present_Count[_Wheel];

	return _RPM[_Wheel];
}


float Kp_Wheel[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB
float Ki_Wheel[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB
float Kd_Wheel[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB

float min_speed[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB
float max_speed[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB


void Setup_PID_LF(float Kp_LF ,float Ki_LF ,float Kd_LF ,float min_speed_LF ,float max_speed_LF){
	Kp_Wheel[0] = Kp_LF;
	Ki_Wheel[0] = Ki_LF;
	Kd_Wheel[0] = Kd_LF;

	min_speed[0] = min_speed_LF;
	max_speed[0] = max_speed_LF;
}

void Setup_PID_LB(float Kp_LB ,float Ki_LB ,float Kd_LB ,float min_speed_LB ,float max_speed_LB){
	Kp_Wheel[1] = Kp_LB;
	Ki_Wheel[1] = Ki_LB;
	Kd_Wheel[1] = Kd_LB;

	min_speed[1] = min_speed_LB;
	max_speed[1] = max_speed_LB;
}

void Setup_PID_RF(float Kp_RF ,float Ki_RF ,float Kd_RF ,float min_speed_RF ,float max_speed_RF){
	Kp_Wheel[2] = Kp_RF;
	Ki_Wheel[2] = Ki_RF;
	Kd_Wheel[2] = Kd_RF;

	min_speed[2] = min_speed_RF;
	max_speed[2] = max_speed_RF;
}

void Setup_PID_RB(float Kp_RB ,float Ki_RB ,float Kd_RB ,float min_speed_RB ,float max_speed_RB){
	Kp_Wheel[3] = Kp_RB;
	Ki_Wheel[3] = Ki_RB;
	Kd_Wheel[3] = Kd_RB;

	min_speed[3] = min_speed_RB;
	max_speed[3] = max_speed_RB;
}


float Error_Speed[4]  = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB

float Proportional[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB
float Integnator[4]   = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB
float Derivative[4]   = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB

float Past_Error[4]   = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB

float Output_PID[4]    = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB

float PID_Speed(float _Setpoint ,uint8_t _Wheel){
	switch (_Wheel) {
	  case 0 : getRPM_TIM_Wheel(TIM_1 ,LF ); break;
	  case 1 : getRPM_TIM_Wheel(TIM_3 ,LB ); break;
	  case 2 : getRPM_TIM_Wheel(TIM_2 ,RF ); break;
	  case 3 : getRPM_LPTIM_Wheel(LPTIM ,RB ); break;
	}

	Error_Speed[_Wheel] = _Setpoint-_RPM[_Wheel];

	Proportional[_Wheel] = Error_Speed[_Wheel];
	Integnator[_Wheel]   += Error_Speed[_Wheel];
	Derivative[_Wheel]   = Error_Speed[_Wheel] - Past_Error[_Wheel];

	Past_Error[_Wheel] = Error_Speed[_Wheel];

	Output_PID[_Wheel]  = (float)((Proportional[_Wheel]*Kp_Wheel[_Wheel]) + (Integnator[_Wheel]*Ki_Wheel[_Wheel]) + (Derivative[_Wheel]*Kd_Wheel[_Wheel]));


	return Output_PID[_Wheel];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////Motor////////////////////////////////////////////////////////////////////
void Motor_DutyCycle_LF(int16_t DutyCycle_LF){
	TIM_15_CH2->Instance->CCR2 = (int16_t)DutyCycle_LF;

	digitalWrite(IN1_LF , (DutyCycle_LF < 0) ? 0 : 1);
	digitalWrite(IN2_LF , (DutyCycle_LF < 0) ? 1 : 0);
}

void Motor_DutyCycle_LB(int16_t DutyCycle_LB){
	TIM_15_CH1->Instance->CCR1 = (int16_t)DutyCycle_LB;

	digitalWrite(IN1_LB , (DutyCycle_LB < 0) ? 0 : 1);
	digitalWrite(IN2_LB , (DutyCycle_LB < 0) ? 1 : 0);
}

void Motor_DutyCycle_RF(int16_t DutyCycle_RF){
	TIM_14->Instance->CCR1 = (int16_t)DutyCycle_RF;

	digitalWrite(IN1_RF , (DutyCycle_RF < 0) ? 0 : 1);
	digitalWrite(IN2_RF , (DutyCycle_RF < 0) ? 1 : 0);
}

void Motor_DutyCycle_RB(int16_t DutyCycle_RB){
	TIM_16->Instance->CCR1 = (int16_t)DutyCycle_RB;

	digitalWrite(IN1_RB , (DutyCycle_RB < 0) ? 0 : 1);
	digitalWrite(IN2_RB , (DutyCycle_RB < 0) ? 1 : 0);
}

float Duty_Cycle[4] = {0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB

float Motor_Speed_LF(int16_t RPM_LF){
	if (RPM_LF > max_speed[0]) {
	   RPM_LF = max_speed[0];
	} else if (RPM_LF < -max_speed[0]) {
	   RPM_LF = -max_speed[0];
	}

	PID_Speed((float)RPM_LF, 0);

	Duty_Cycle[0] = (Output_PID[0] / (float)(max_speed[0] - min_speed[0])) * (float)(TIM_15_CH2->Init.Period);

	TIM_15_CH2->Instance->CCR2 = (int16_t)fabsf(Duty_Cycle[0]);

	digitalWrite(IN1_LF, (Duty_Cycle[0] < 0) ? 0 : 1);
	digitalWrite(IN2_LF, (Duty_Cycle[0] < 0) ? 1 : 0);

	return _RPM[0];
}

float Motor_Speed_LB(int16_t RPM_LB){
	if (RPM_LB > max_speed[1]) {
	   RPM_LB = max_speed[1];
	} else if (RPM_LB < -max_speed[1]) {
	   RPM_LB = -max_speed[1];
	}

	PID_Speed((float)RPM_LB ,1);

	Duty_Cycle[1] = (Output_PID[1]/((float)(max_speed[1] - min_speed[1]))) * ((float)(TIM_15_CH1->Init.Period));

	TIM_15_CH1->Instance->CCR1 = (int16_t)fabs(Duty_Cycle[1]);

	digitalWrite(IN1_LB , (Duty_Cycle[1] < 0) ? 0 : 1);
	digitalWrite(IN2_LB , (Duty_Cycle[1] < 0) ? 1 : 0);

	return _RPM[1];
}

float Motor_Speed_RF(int16_t RPM_RF){
	if (RPM_RF > max_speed[2]) {
	   RPM_RF = max_speed[2];
	} else if (RPM_RF < -max_speed[2]) {
	   RPM_RF = -max_speed[2];
	}

	PID_Speed((float)RPM_RF ,2);

	Duty_Cycle[2] = (Output_PID[2]/((float)(max_speed[2] - min_speed[2]))) * ((float)(TIM_14->Init.Period));

	TIM_14->Instance->CCR1 = (int16_t)fabs(Duty_Cycle[2]);

	digitalWrite(IN1_RF , (Duty_Cycle[2] < 0) ? 0 : 1);
	digitalWrite(IN2_RF , (Duty_Cycle[2] < 0) ? 1 : 0);

	return _RPM[2];
}

float Motor_Speed_RB(int16_t RPM_RB){
	if (RPM_RB > max_speed[3]) {
		RPM_RB = max_speed[3];
	} else if (RPM_RB < -max_speed[3]) {
		RPM_RB = -max_speed[3];
	}

	PID_Speed((float)RPM_RB ,3);

	Duty_Cycle[3] = (Output_PID[3]/((float)(max_speed[3] - min_speed[3]))) * ((float)(TIM_16->Init.Period));

	TIM_16->Instance->CCR1 = (int16_t)fabs(Duty_Cycle[3]);

	digitalWrite(IN1_RB , (Duty_Cycle[3] < 0) ? 0 : 1);
	digitalWrite(IN2_RB , (Duty_Cycle[3] < 0) ? 1 : 0);

	return _RPM[3];
}

//uint8_t PIN;

void digitalWrite(char* _PIN , uint8_t vlue){
	uint8_t PIN = (_PIN[2] - '0') * 10 + (_PIN[3] - '0');

	if (_PIN[1] == 'A') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'B') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'C') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, vlue); break;
	        }
	    } else if (_PIN[1] == 'D') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, vlue); break;
	        }
	    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

