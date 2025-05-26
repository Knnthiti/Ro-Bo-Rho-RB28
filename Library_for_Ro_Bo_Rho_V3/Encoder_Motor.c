/*
 * Encoder.c
 *
 *  Created on: Nov 1, 2024
 *      Author: Knnn
 */
#include "Encoder_Motor.h"

//pin for Ro_Bo_Rho
TIM_HandleTypeDef *EN_LF; //_TIM_5
TIM_HandleTypeDef *EN_LB; //_TIM_1
TIM_HandleTypeDef *EN_RF; //_TIM_8
TIM_HandleTypeDef *EN_RB; //_TIM_4
TIM_HandleTypeDef *EN_X; //_TIM_2
TIM_HandleTypeDef *EN_Y; //_TIM_3


TIM_HandleTypeDef *LF_PWM; //_TIM_14_CH1
TIM_HandleTypeDef *LB_PWM; //_TIM_12_CH1
TIM_HandleTypeDef *RF_PWM; //_TIM_11_CH1
TIM_HandleTypeDef *RB_PWM; //_TIM_12_CH2
TIM_HandleTypeDef *EXTRA1_PWM; //_TIM_9_CH1
TIM_HandleTypeDef *EXTRA2_PWM; //_TIM_10_CH1


///////////////////////////////////////////////////////////Setup_MOTOR/////////////////////////////////////////////////////
_Motor Motor_feedback;

Setup_Motor _Setup = {
    ._freq = 100,
    .CPR = 68,
    .Gear_Ratio = 27
};

int16_t DutyCycle_LF_MAX = 0;
int16_t DutyCycle_LB_MAX = 0;
int16_t DutyCycle_RF_MAX = 0;
int16_t DutyCycle_RB_MAX = 0;
int16_t DutyCycle_EXTRA1_MAX = 0;
int16_t DutyCycle_EXTRA2_MAX = 0;

char* IN_LF;
char* IN_LB;
char* IN_RF;
char* IN_RB;
char* IN_EXTRA1;
char* IN_EXTRA2;

void Motor_setup_LF(TIM_HandleTypeDef *_TIM_14_CH1 ,TIM_HandleTypeDef *_TIM_5  ,char* _IN_LF){
	//Motor_setup_LF(PWM_TIM ,Encoder_TIM   ,IN_LF);

	LF_PWM = _TIM_14_CH1;
	EN_LF      = _TIM_5;

	HAL_TIM_PWM_Start(LF_PWM, TIM_CHANNEL_1);       //PWM
	HAL_TIM_Encoder_Start(EN_LF , TIM_CHANNEL_ALL);     //Encoder

	IN_LF = _IN_LF;

	DutyCycle_LF_MAX = (LF_PWM->Init.Period);

}

void Motor_setup_LB(TIM_HandleTypeDef *_TIM_12_CH1 ,TIM_HandleTypeDef *_TIM_1  ,char* _IN_LB){
    //Motor_setup_LB(PWM_TIM ,Encoder_TIM  ,IN1_LB ,IN2_LB);

	LB_PWM = _TIM_12_CH1;
	EN_LB      = _TIM_1;

	HAL_TIM_PWM_Start(LB_PWM, TIM_CHANNEL_1);       //PWM
	HAL_TIM_Encoder_Start(EN_LB , TIM_CHANNEL_ALL);     //Encoder

	IN_LB = _IN_LB;

	DutyCycle_LB_MAX = (LB_PWM->Init.Period);

}

void Motor_setup_RF(TIM_HandleTypeDef *_TIM_11_CH1  ,TIM_HandleTypeDef *_TIM_8  ,char* _IN_RF){
    //Motor_setup_RF(PWM_TIM ,Encoder_TIM   ,IN1_RF ,IN2_RF);

	RF_PWM = _TIM_11_CH1;
	EN_RF  = _TIM_8;

	HAL_TIM_PWM_Start(RF_PWM, TIM_CHANNEL_1);           //PWM
	HAL_TIM_Encoder_Start(EN_RF , TIM_CHANNEL_ALL);     //Encoder

	IN_RF = _IN_RF;

	DutyCycle_RF_MAX = (RF_PWM->Init.Period);

}

void Motor_setup_RB(TIM_HandleTypeDef *_TIM_12_CH2   ,TIM_HandleTypeDef *_TIM_4 ,char* _IN_RB){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,IN1_RB ,IN2_RB);

	RB_PWM = _TIM_12_CH2;
	EN_RB  = _TIM_4;

	HAL_TIM_PWM_Start(RB_PWM, TIM_CHANNEL_2);            //PWM
	HAL_TIM_Encoder_Start(EN_RB , TIM_CHANNEL_ALL);      //Encoder

	IN_RB = _IN_RB;

	DutyCycle_RB_MAX = (RB_PWM->Init.Period);

}

void Motor_setup_EXTRA1(TIM_HandleTypeDef *_TIM_9_CH1  ,TIM_HandleTypeDef *_TIM_3  ,char* _IN_EXTRA1){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,IN1_RB ,IN2_RB);

	EXTRA1_PWM = _TIM_9_CH1;
	EN_X  = _TIM_3;

	HAL_TIM_PWM_Start(EXTRA1_PWM, TIM_CHANNEL_1);            //PWM
	HAL_TIM_Encoder_Start(EN_X , TIM_CHANNEL_ALL);      //Encoder

	IN_EXTRA1 = _IN_EXTRA1;

	DutyCycle_EXTRA1_MAX = (EXTRA1_PWM->Init.Period);

}

void Motor_setup_EXTRA2(TIM_HandleTypeDef *_TIM_10_CH1  ,TIM_HandleTypeDef *_TIM_2 ,char* _IN_EXTRA2){
    //Motor_setup_RB(PWM_TIM ,Encoder_TIM   ,IN1_RB ,IN2_RB);

	EXTRA2_PWM = _TIM_10_CH1;
	EN_Y  = _TIM_2;

	HAL_TIM_PWM_Start(EXTRA2_PWM, TIM_CHANNEL_1);            //PWM
	HAL_TIM_Encoder_Start(EN_Y , TIM_CHANNEL_ALL);      //Encoder

	IN_EXTRA2 = _IN_EXTRA2;

	DutyCycle_EXTRA2_MAX = (EXTRA2_PWM->Init.Period);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////RPM///////////////////////////////////////////////////////////////

int32_t getCount(TIM_HandleTypeDef *TIM ,motor_Wheel _Wheel){
	Motor_feedback._Count[_Wheel] = ((int32_t)(TIM->Instance->CNT));

	return Motor_feedback._Count[_Wheel];
}

void Setup_frequency_Motor(uint16_t freq){
	_Setup._freq = freq;
}

void Setup_CPR(uint16_t _CPR){
	_Setup.CPR = _CPR;
}

void Setup_Gear_Ratio(uint16_t _Gear_Ratio){
	_Setup.Gear_Ratio = _Gear_Ratio;
}

float getRPM_to_Rad_s(float RPM){
	float Rad_s = RPM * 0.10472f;

	return Rad_s;
}

float getRad_s_to_RPM(float Rad_s){
	float RPM__ = Rad_s * 9.549297f;

	return RPM__;
}


int16_t Present_Count[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
int16_t Past_Count[6] = {0 ,0 ,0 ,0 ,0 ,0};    //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float getRPM_TIM_Wheel(TIM_HandleTypeDef *TIM ,motor_Wheel _Wheel){
	if(_Wheel == 1){
		Present_Count[_Wheel] = (int16_t)-getCount(TIM ,_Wheel);
	}else{
		Present_Count[_Wheel] = (int16_t)getCount(TIM ,_Wheel);
	}

	// V = count/t = count*freq
	Motor_feedback._RPM[_Wheel] = (float)((int16_t)(Present_Count[_Wheel] - Past_Count[_Wheel]) * _Setup._freq);
	Motor_feedback._RPM[_Wheel] = (float)(((Motor_feedback._RPM[_Wheel]* 60.0f)/_Setup.CPR )/_Setup.Gear_Ratio);

	Past_Count[_Wheel] = Present_Count[_Wheel];

	return Motor_feedback._RPM[_Wheel];
}

/////////////////////////////////////////////////////////////////PID//////////////////////////////////////////////////////////////////////
float Kp_Wheel[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Ki_Wheel[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Kd_Wheel[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float min_speed[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float max_speed[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2


void Setup_PID_Wheel(float Kp ,float Ki ,float Kd ,float _min_speed ,float _max_speed ,motor_Wheel _Wheel){
	Kp_Wheel[_Wheel] = Kp;
	Ki_Wheel[_Wheel] = Ki;
	Kd_Wheel[_Wheel] = Kd;

	min_speed[_Wheel] = _min_speed;
	max_speed[_Wheel] = _max_speed;
}



float Error_Speed[6]  = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Proportional[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Integnator[6]   = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2
float Derivative[6]   = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Past_Error[6]   = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float PID_Speed(float _Setpoint ,float RPM ,motor_Wheel _Wheel){
	Error_Speed[_Wheel] = _Setpoint-RPM;

	Proportional[_Wheel] = Error_Speed[_Wheel];
	Integnator[_Wheel] += Error_Speed[_Wheel];
	if (Integnator[_Wheel] > 25000) {
		Integnator[_Wheel] = 25000;
	} else if (Integnator[_Wheel] < -25000) {
		Integnator[_Wheel] = -25000;
	} else if (_Setpoint == 0) {
		Integnator[_Wheel] = 0;
	}

	Derivative[_Wheel]   = Error_Speed[_Wheel] - Past_Error[_Wheel];

	Past_Error[_Wheel] = Error_Speed[_Wheel];

	Motor_feedback._PID[_Wheel]  = (float)((Proportional[_Wheel]*Kp_Wheel[_Wheel]) + (Integnator[_Wheel]*Ki_Wheel[_Wheel]) + (Derivative[_Wheel]*Kd_Wheel[_Wheel]));

	if (Motor_feedback._PID[_Wheel] > max_speed[_Wheel]) {
		Motor_feedback._PID[_Wheel] = max_speed[_Wheel];
	} else if (Motor_feedback._PID[_Wheel] < -max_speed[_Wheel]) {
		Motor_feedback._PID[_Wheel] = -max_speed[_Wheel];
	}

	return Motor_feedback._PID[_Wheel];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////Motor////////////////////////////////////////////////////////////////////
void Motor_DutyCycle_LF(int16_t DutyCycle_LF){
	if (DutyCycle_LF > DutyCycle_LF_MAX) {
	    DutyCycle_LF = DutyCycle_LF_MAX;
	} else if (DutyCycle_LF < -DutyCycle_LF_MAX) {
		DutyCycle_LF = -DutyCycle_LF_MAX;
	}

	LF_PWM->Instance->CCR1 = (DutyCycle_LF > 0) ? (int16_t)DutyCycle_LF : (DutyCycle_LF_MAX + (int16_t)DutyCycle_LF);

	digitalWrite(IN_LF , (DutyCycle_LF < 0) ? 1 : 0);

	if(DutyCycle_LF == 0){
	   LF_PWM->Instance->CCR1 = 0;
	   digitalWrite(IN_LF ,0);
	}
}

void Motor_DutyCycle_LB(int16_t DutyCycle_LB){
	DutyCycle_LB = -DutyCycle_LB;
	if (DutyCycle_LB > DutyCycle_LB_MAX) {
		DutyCycle_LB = DutyCycle_LB_MAX;
	} else if (DutyCycle_LB < -DutyCycle_LB_MAX) {
		DutyCycle_LB = -DutyCycle_LB_MAX;
	}

	LB_PWM->Instance->CCR1 = (DutyCycle_LB > 0) ? (int16_t)DutyCycle_LB : (DutyCycle_LB_MAX + (int16_t)DutyCycle_LB);

	digitalWrite(IN_LB , (DutyCycle_LB < 0) ? 1 : 0);

	if(DutyCycle_LB == 0){
	   LB_PWM->Instance->CCR1 = 0;
	   digitalWrite(IN_LB ,0);
	}
}

void Motor_DutyCycle_RF(int16_t DutyCycle_RF){
	DutyCycle_RF = -DutyCycle_RF;
	if (DutyCycle_RF > DutyCycle_RF_MAX) {
		DutyCycle_RF = DutyCycle_RF_MAX;
	} else if (DutyCycle_RF < -DutyCycle_RF_MAX) {
		DutyCycle_RF = -DutyCycle_RF_MAX;
	}

	RF_PWM->Instance->CCR1 = (DutyCycle_RF > 0) ? (int16_t)DutyCycle_RF : (DutyCycle_RF_MAX + (int16_t)DutyCycle_RF);

	digitalWrite(IN_RF , (DutyCycle_RF < 0) ? 1 : 0);

	if(DutyCycle_RF == 0){
	   RF_PWM->Instance->CCR1 = 0;
	   digitalWrite(IN_RF ,0);
	}
}

void Motor_DutyCycle_RB(int16_t DutyCycle_RB){
	if (DutyCycle_RB > DutyCycle_RB_MAX) {
		DutyCycle_RB = DutyCycle_RB_MAX;
	} else if (DutyCycle_RB < -DutyCycle_RB_MAX) {
	    DutyCycle_RB = -DutyCycle_RB_MAX;
	}

	RB_PWM->Instance->CCR2 = (DutyCycle_RB > 0) ? (int16_t)DutyCycle_RB : (DutyCycle_RB_MAX + (int16_t)DutyCycle_RB);

	digitalWrite(IN_RB , (DutyCycle_RB < 0) ? 1 : 0);

	if(DutyCycle_RB == 0){
	    RB_PWM->Instance->CCR2 = 0;
		digitalWrite(IN_RB ,0);
	}
}

void Motor_DutyCycle_EXTRA1(int16_t DutyCycle_EXTRA1){
	if (DutyCycle_EXTRA1 > DutyCycle_EXTRA1_MAX) {
		DutyCycle_EXTRA1 = DutyCycle_EXTRA1_MAX;
	} else if (DutyCycle_EXTRA1 < -DutyCycle_EXTRA1_MAX) {
		DutyCycle_EXTRA1 = -DutyCycle_EXTRA1_MAX;
	}

	EXTRA1_PWM->Instance->CCR1 = (DutyCycle_EXTRA1 > 0) ? (int16_t)DutyCycle_EXTRA1 : (DutyCycle_EXTRA1_MAX + (int16_t)DutyCycle_EXTRA1);

	digitalWrite(IN_EXTRA1 , (DutyCycle_EXTRA1 < 0) ? 1 : 0);

	if(DutyCycle_EXTRA1 == 0){
		EXTRA1_PWM->Instance->CCR1 = 0;
	    digitalWrite(IN_EXTRA1 ,0);
	}
}

void Motor_DutyCycle_EXTRA2(int16_t DutyCycle_EXTRA2){
	if (DutyCycle_EXTRA2 > DutyCycle_EXTRA2_MAX) {
		DutyCycle_EXTRA2 = DutyCycle_EXTRA2_MAX;
	} else if (DutyCycle_EXTRA2 < -DutyCycle_EXTRA2_MAX) {
		DutyCycle_EXTRA2 = -DutyCycle_EXTRA2_MAX;
	}

	EXTRA2_PWM->Instance->CCR1 = (DutyCycle_EXTRA2 > 0) ? (int16_t)DutyCycle_EXTRA2 : (DutyCycle_EXTRA2_MAX + (int16_t)DutyCycle_EXTRA2);

	digitalWrite(IN_EXTRA2 , (DutyCycle_EXTRA2 < 0) ? 1 : 0);

	if(DutyCycle_EXTRA2 == 0){
	     EXTRA2_PWM->Instance->CCR1 = 0;
		 digitalWrite(IN_EXTRA2 ,0);
	}
}

int16_t Duty_Cycle[6] = {0 ,0 ,0 ,0 ,0 ,0}; //LF ,LB ,RF ,RB ,EXTRA1 ,EXTRA2

float Motor_Speed_LF(int16_t RPM_INPUT ,float RPM_LF){
	if (RPM_LF > max_speed[0]) {
	   RPM_LF = max_speed[0];
	} else if (RPM_LF < -max_speed[0]) {
	   RPM_LF = -max_speed[0];
	}

	PID_Speed(RPM_INPUT ,RPM_LF , 0);

	Duty_Cycle[0] = (int16_t)((Motor_feedback._PID[0] / ((float)(max_speed[0] - min_speed[0]))) * DutyCycle_LF_MAX);

	Motor_DutyCycle_LF(Duty_Cycle[0]);

	return Motor_feedback._PID[0];
}

float Motor_Speed_LB(int16_t RPM_INPUT ,float RPM_LB){
	if (RPM_LB > max_speed[1]) {
	   RPM_LB = max_speed[1];
	} else if (RPM_LB < -max_speed[1]) {
	   RPM_LB = -max_speed[1];
	}

	PID_Speed(RPM_INPUT ,RPM_LB ,1);

	Duty_Cycle[1] = (int16_t)((Motor_feedback._PID[1]/((float)(max_speed[1] - min_speed[1]))) * DutyCycle_LB_MAX);

	Motor_DutyCycle_LB(Duty_Cycle[1]);

	return Motor_feedback._PID[1];
}

float Motor_Speed_RF(int16_t RPM_INPUT ,float RPM_RF){
	if (RPM_RF > max_speed[2]) {
	   RPM_RF = max_speed[2];
	} else if (RPM_RF < -max_speed[2]) {
	   RPM_RF = -max_speed[2];
	}

	PID_Speed(RPM_INPUT ,RPM_RF ,2);

	Duty_Cycle[2] = (int16_t)((Motor_feedback._PID[2]/((float)(max_speed[2] - min_speed[2]))) * DutyCycle_RF_MAX);

	Motor_DutyCycle_RF(Duty_Cycle[2]);

	return Motor_feedback._PID[2];
}

float Motor_Speed_RB(int16_t RPM_INPUT ,float RPM_RB){
	if (RPM_RB > max_speed[3]) {
		RPM_RB = max_speed[3];
	} else if (RPM_RB < -max_speed[3]) {
		RPM_RB = -max_speed[3];
	}

	PID_Speed(RPM_INPUT ,RPM_RB ,3);

	Duty_Cycle[3] = (int16_t)((Motor_feedback._PID[3]/((float)(max_speed[3] - min_speed[3]))) * DutyCycle_RB_MAX);

	Motor_DutyCycle_RB(Duty_Cycle[3]);

	return Motor_feedback._PID[3];
}

float Motor_Speed_EXTRA1(int16_t RPM_INPUT ,float RPM_EXTRA1){
	if (RPM_EXTRA1 > max_speed[4]) {
		RPM_EXTRA1 = max_speed[4];
	} else if (RPM_EXTRA1 < -max_speed[4]) {
		RPM_EXTRA1 = -max_speed[4];
	}

	PID_Speed(RPM_INPUT ,RPM_EXTRA1 ,4);

	Duty_Cycle[4] = (int16_t)((Motor_feedback._PID[4]/((float)(max_speed[4] - min_speed[4]))) * DutyCycle_EXTRA1_MAX);

	Motor_DutyCycle_EXTRA1(Duty_Cycle[4]);

	return Motor_feedback._PID[4];
}

float Motor_Speed_EXTRA2(int16_t RPM_INPUT ,float RPM_EXTRA2){
	if (RPM_EXTRA2 > max_speed[5]) {
		RPM_EXTRA2 = max_speed[5];
	} else if (RPM_EXTRA2 < -max_speed[5]) {
		RPM_EXTRA2 = -max_speed[5];
	}

	PID_Speed(RPM_INPUT ,RPM_EXTRA2 ,5);

	Duty_Cycle[5] = (int16_t)((Motor_feedback._PID[5]/((float)(max_speed[5] - min_speed[5]))) * DutyCycle_EXTRA2_MAX);

	Motor_DutyCycle_EXTRA2(Duty_Cycle[5]);

	return Motor_feedback._PID[5];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

