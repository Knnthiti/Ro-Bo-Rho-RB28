/*
 * Arduino.c
 *
 *  Created on: May 22, 2025
 *      Author: Knnn
 */
#include "Arduino.h"

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
	    } else if (_PIN[1] == 'E') {
	        switch (PIN) {
	            case 0: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_0, vlue); break;
	            case 1: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, vlue); break;
	            case 2: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_2, vlue); break;
	            case 3: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, vlue); break;
	            case 4: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, vlue); break;
	            case 5: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, vlue); break;
	            case 6: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, vlue); break;
	            case 7: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, vlue); break;
	            case 8: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_8, vlue); break;
	            case 9: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_9, vlue); break;
	            case 10: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_10, vlue); break;
	            case 11: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_11, vlue); break;
	            case 12: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_12, vlue); break;
	            case 13: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_13, vlue); break;
	            case 14: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_14, vlue); break;
	            case 15: HAL_GPIO_WritePin(GPIOE, GPIO_PIN_15, vlue); break;
	        }
	    }
}

uint8_t digitalRead(char *_PIN) {
	uint8_t PIN = (_PIN[2] - '0') * 10 + (_PIN[3] - '0');
	uint8_t value;

	if (_PIN[1] == 'A') {
		switch (PIN) {
		case 0:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
			break;
		case 1:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
			break;
		case 2:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
			break;
		case 3:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
			break;
		case 4:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
			break;
		case 5:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
			break;
		case 6:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
			break;
		case 7:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
			break;
		case 8:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8);
			break;
		case 9:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9);
			break;
		case 10:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
			break;
		case 11:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11);
			break;
		case 12:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_12);
			break;
		case 13:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13);
			break;
		case 14:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_14);
			break;
		case 15:
			value = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);
			break;
		}
	} else if (_PIN[1] == 'B') {
		switch (PIN) {
		case 0:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
			break;
		case 1:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
			break;
		case 2:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);
			break;
		case 3:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);
			break;
		case 4:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
			break;
		case 5:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
			break;
		case 6:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6);
			break;
		case 7:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7);
			break;
		case 8:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
			break;
		case 9:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9);
			break;
		case 10:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
			break;
		case 11:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11);
			break;
		case 12:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
			break;
		case 13:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
			break;
		case 14:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
			break;
		case 15:
			value = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
			break;
		}
	} else if (_PIN[1] == 'C') {
		switch (PIN) {
		case 0:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0);
			break;
		case 1:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);
			break;
		case 2:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2);
			break;
		case 3:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3);
			break;
		case 4:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4);
			break;
		case 5:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5);
			break;
		case 6:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
			break;
		case 7:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_7);
			break;
		case 8:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);
			break;
		case 9:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9);
			break;
		case 10:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
			break;
		case 11:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);
			break;
		case 12:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);
			break;
		case 13:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
			break;
		case 14:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
			break;
		case 15:
			value = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
			break;
		}
	} else if (_PIN[1] == 'D') {
		switch (PIN) {
		case 0:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_0);
			break;
		case 1:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1);
			break;
		case 2:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2);
			break;
		case 3:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_3);
			break;
		case 4:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4);
			break;
		case 5:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5);
			break;
		case 6:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_6);
			break;
		case 7:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7);
			break;
		case 8:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_8);
			break;
		case 9:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9);
			break;
		case 10:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_10);
			break;
		case 11:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_11);
			break;
		case 12:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12);
			break;
		case 13:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_13);
			break;
		case 14:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14);
			break;
		case 15:
			value = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15);
			break;
		}
	} else if (_PIN[1] == 'E') {
		switch (PIN) {
		case 0:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_0);
			break;
		case 1:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_1);
			break;
		case 2:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2);
			break;
		case 3:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3);
			break;
		case 4:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4);
			break;
		case 5:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
			break;
		case 6:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6);
			break;
		case 7:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7);
			break;
		case 8:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8);
			break;
		case 9:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);
			break;
		case 10:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_10);
			break;
		case 11:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11);
			break;
		case 12:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_12);
			break;
		case 13:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_13);
			break;
		case 14:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_14);
			break;
		case 15:
			value = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15);
			break;
		}
	}
	return value;
}

float map(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
    return toLow + (toHigh - toLow) * ((value - fromLow) / (fromHigh - fromLow));
}
