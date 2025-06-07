/*
 * Game_Play.c
 *
 *  Created on: Apr 25, 2025
 *      Author: Knnn
 */

#include "Game_Play.h"

uint8_t Reset = 0;

uint8_t Past_move4 = 0;

long Time_GUN = 0;
float __Degree = 0.0f;
uint8_t Past_attack1 = 0;

uint8_t Past_attack2 = 0;

long Time_Juggling = 0;
uint8_t _Case_Juggling = 0;
uint8_t Past_attack3 = 0;

long Time_Reload = 0;
uint8_t _Case_Reload = 0;
uint8_t Past_attack4 = 0;
uint8_t Past_ball = 0;

typedef struct {
	uint8_t status_GUN;
	uint8_t status_Reload;
	uint8_t status_Juggling;
} Robot;

Robot Status_Robot;

void Juggling(TIM_HandleTypeDef *PIN_PWM) {
	switch (_Case_Juggling) {
	case 0:
		if ((Status_Robot.status_Juggling == 1)
				&& ((uwTick - Time_Juggling) >= 888)) {
			digitalWrite("PA05", 1);
			_Case_Juggling = 1;
		}
		break;
	case 1:
		if ((Status_Robot.status_Juggling == 1)
				&& ((uwTick - Time_Juggling) >= 1500)) {
			digitalWrite("PA05", 0);
//			Motor_DutyCycle_EXTRA2(-1000);
			Motor_DutyCycle(PIN_PWM, Servo1, "PB00", -1500);
			_Case_Juggling = 2;
		}
		break;
	case 2:
		if ((Status_Robot.status_Juggling == 1)
				&& ((uwTick - Time_Juggling) >= 2500)) {
			Status_Robot.status_Juggling = 0;
//			Motor_DutyCycle_EXTRA2(0);
			Motor_DutyCycle(PIN_PWM, Servo1, "PB00", 0);
			Motor_DutyCycle_EXTRA2(1500);
			_Case_Juggling = 0;
		}
		break;
	}

}

void Reload() {
	switch (_Case_Reload) {
	case 0:
		if ((Status_Robot.status_Reload == 1)
				&& ((uwTick - Time_Reload) >= 500)) {
			digitalWrite("PC00", 1);
			_Case_Reload = 1;
		}
		break;
	case 1:
		if ((Status_Robot.status_Reload == 1)
				&& ((uwTick - Time_Reload) >= 2000)) {
			digitalWrite("PC00", 0);
//				Motor_DutyCycle(PIN_PWM, Servo1, "PB00", 0);
			_Case_Reload = 2;
		}
		break;
	case 2:
		if ((Status_Robot.status_Reload == 1)
					&& ((uwTick - Time_Reload) >= 3000)) {
			Status_Robot.status_Reload = 0;
			Motor_DutyCycle_EXTRA2(0);
			_Case_Reload = 0;
		}
	break;
	}
}

void Shoot_Ball() {
	if (Status_Robot.status_GUN == 1) {
		digitalWrite("PC01", 1);
	}

	if ((Status_Robot.status_GUN == 1) && ((uwTick - Time_GUN) >= 500)) {
		digitalWrite("PC01", 0);
//		Motor_DutyCycle(PIN_PWM, Servo1, "PB00", 0);
		Motor_DutyCycle_EXTRA2(0);
		Status_Robot.status_GUN = 0;
	}

}

void Game_RUN(TIM_HandleTypeDef *PIN_PWM, TIM_HandleTypeDef *_Encoder) {
	///////////////////////////////////////////////////Set up Juggling///////////////////////////////////////////////////
	if ((Str_PS2.moveBtnBit.move4 == 1) && (Past_move4 == 0)) {
		//		Motor_DutyCycle_EXTRA2(500);
		Motor_DutyCycle(PIN_PWM, Servo1, "PB00", 1000);
		digitalWrite("PA04", 1);
	}
	Past_move4 = Str_PS2.moveBtnBit.move4;
	///////////////////////////////////////////////////Set up Juggling///////////////////////////////////////////////////

	///////////////////////////////////////////////////_Juggling///////////////////////////////////////////////////
	__Degree = __Degree - Str_PS2.stickValue[2];
	if ((Str_PS2.attackBtnBit.attack3 == 1) && (Past_attack3 == 0)) {
		Time_Juggling = uwTick;
		digitalWrite("PA04", 0);
//		__Degree = 0.0f;
		Status_Robot.status_Juggling = 1;
	}
	Juggling(PIN_PWM);
	Past_attack3 = Str_PS2.attackBtnBit.attack3;
	///////////////////////////////////////////////////_Juggling///////////////////////////////////////////////////

	///////////////////////////////////////////////////_Reload///////////////////////////////////////////////////
	if ((Str_PS2.attackBtnBit.attack4 == 1) && (Past_attack4 == 0)) {
		Time_Reload = uwTick;

		//		Motor_DutyCycle(PIN_PWM, Servo1, "PB00", -1000);
		//		Motor_DutyCycle_EXTRA2(1000);
		Status_Robot.status_Reload = 1;
	}
	Reload();
	///////////////////////////////////////////////////_Reload///////////////////////////////////////////////////

	///////////////////////////////////////////////////_charge_Ball///////////////////////////////////////////////////
	if ((Str_PS2.attackBtnBit.attack2 == 1) && (Past_attack2 == 0)) {
		//		Motor_DutyCycle(PIN_PWM, Servo1, "PB00", 4000);
		Motor_DutyCycle_EXTRA2(-4000);
//		__Degree = -135.0f;
	}
	Past_attack2 = Str_PS2.attackBtnBit.attack2;

//	if(digitalRead("PE07") == 0){
		Motor_DutyCycle_EXTRA1(Ramp_Count(__Degree, Count_to_degree(getCount(_Encoder, _EXTRA1))));
//	}else if((__Degree == 0) && (digitalRead("PE07") == 0)){
//		Motor_DutyCycle_EXTRA1(500);
//	}else{
	if((digitalRead("PE15") == 0) && (Past_ball == 1)){
		Motor_DutyCycle_EXTRA1(0);
		__Degree = 0;
		Error_degree = 0;
		Proportiona_degree = 0;
		Integnator_degree = 0;
		Derivative_degree = 0;
		Past_Error_degree = 0;
	}
	Past_ball = digitalRead("PE15");

	Past_attack4 = Str_PS2.attackBtnBit.attack4;
	///////////////////////////////////////////////////_charge_Ball///////////////////////////////////////////////////

	///////////////////////////////////////////////////_Shoot_Ball///////////////////////////////////////////////////
	if ((Str_PS2.attackBtnBit.attack1 == 1) && (Past_attack1 == 0)) {
		Time_GUN = uwTick;
		Status_Robot.status_GUN = 1;
	}
	Shoot_Ball();
	Past_attack1 = Str_PS2.attackBtnBit.attack1;
	///////////////////////////////////////////////////_Shoot_Ball///////////////////////////////////////////////////
}

void Game_Play_ROBOT_1(TIM_HandleTypeDef *PIN_PWM, TIM_HandleTypeDef *_Encoder) {
	if ((Str_PS2.moveBtnBit.set1 == 1) && (Reset == 0)){
		Motor_DutyCycle_LF(0);
		Motor_DutyCycle_LB(0);
		Motor_DutyCycle_RF(0);
		Motor_DutyCycle_RB(0);

		Motor_DutyCycle_EXTRA2(0);

		Motor_DutyCycle(PIN_PWM, Servo1, "PB00", 0);

		digitalWrite("PA04", 0);
		digitalWrite("PC00", 0);
		digitalWrite("PC01", 0);

		Status_Robot.status_GUN = 0;
		Status_Robot.status_Reload = 0;
		Status_Robot.status_Juggling = 0;

		Motor_DutyCycle_EXTRA1(0);
		__Degree = 0;
		Error_degree = 0;
		Proportiona_degree = 0;
		Integnator_degree = 0;
		Derivative_degree = 0;
		Past_Error_degree = 0;

		_DutyCycle = 0;

		Motor_feedback._Count[4] = 0;
//		Reset = 0;
	}else{
		Game_RUN(PIN_PWM, _Encoder);
	}
	Reset = Str_PS2.moveBtnBit.set1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Game_Play_ROBOT_2(TIM_HandleTypeDef *_Encoder) {
	if ((Str_PS2.moveBtnBit.set1 == 1) && (Reset == 0)){
		Motor_DutyCycle_LF(0);
		Motor_DutyCycle_LB(0);
		Motor_DutyCycle_RF(0);
		Motor_DutyCycle_RB(0);

		Motor_DutyCycle_EXTRA1(0);
		Motor_DutyCycle_EXTRA2(0);

		digitalWrite("PC01", 0);

	}else{
		if (Str_PS2.attackBtnBit.attack2 == 1) {
		      __Degree = 0;
		} else {
		      __Degree = __Degree + Str_PS2.stickValue[2];
		}

		if (Str_PS2.attackBtnBit.attack3 == 1) {
			Motor_DutyCycle_EXTRA2(-4000);
		} else if (Str_PS2.attackBtnBit.attack4 == 1) {
			Motor_DutyCycle_EXTRA2(2000);
		}else{
			Motor_DutyCycle_EXTRA2(0);
		}

		if (Str_PS2.attackBtnBit.attack1 == 1) {
			digitalWrite("PC01", 1);
		} else if (Str_PS2.attackBtnBit.attack1 == 0) {
			digitalWrite("PC01", 0);
		}

		Motor_DutyCycle_EXTRA1(Ramp_Count(__Degree,Count_to_degree(getCount(_Encoder, _EXTRA1))));

//		    if ((Error_degree > 0) && (__Degree == 0)) {
//		      if (digitalRead("PE13") == 0) {
//		        Motor_DutyCycle_EXTRA1(500);
//		      } else {
//		        Motor_DutyCycle_EXTRA1(0);
//		        Error_degree = 0;
//		        Proportiona_degree = 0;
//		        Integnator_degree = 0;
//		        Derivative_degree = 0;
//		        Past_Error_degree = 0;
//		      }
//		    }else if ((Error_degree < 0) && (__Degree == 0)) {
//		      if (digitalRead("PE13") == 0) {
//		        Motor_DutyCycle_LF(-500);
//		      } else {
//		        Motor_DutyCycle_LF(0);
//		        Error_degree = 0;
//		        Proportiona_degree = 0;
//		        Integnator_degree = 0;
//		        Derivative_degree = 0;
//		        Past_Error_degree = 0;
//		      }
//		    }
	}
	Reset = Str_PS2.moveBtnBit.set1;
}
