/*
 * Game_Play.h
 *
 *  Created on: Apr 25, 2025
 *      Author: Knnn
 */

#ifndef GAME_PLAY_H_
#define GAME_PLAY_H_

#include "main.h"
#include "Encoder_Motor.h"
#include "UART_ESP.h"
#include "Ramp_Robot.h"

void Shoot_Ball();
void Juggling(TIM_HandleTypeDef *PIN_PWM);
void Reload();
void Game_Play_ROBOT_1(TIM_HandleTypeDef *PIN_PWM ,TIM_HandleTypeDef *_Encoder);
void Game_Play_ROBOT_2(TIM_HandleTypeDef *_Encoder);

#endif /* GAME_PLAY_H_ */
