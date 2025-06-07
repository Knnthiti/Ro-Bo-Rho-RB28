/*
 * Arduino.h
 *
 *  Created on: May 22, 2025
 *      Author: Knnn
 */

#ifndef ARDUINO_H_
#define ARDUINO_H_

#include "string.h"
#include "stdint.h"
#include "stdlib.h"

#include "math.h"
#include "stm32f4xx.h"

#include "main.h"

void digitalWrite(char* _PIN, uint8_t vlue);
uint8_t digitalRead(char* _PIN);
float map(float value, float fromLow, float fromHigh, float toLow, float toHigh);


#endif /* ARDUINO_H_ */
