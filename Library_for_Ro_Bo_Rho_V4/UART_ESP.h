/*
 * UART_ESP.h
 *
 *  Created on: May 6, 2025
 *      Author: Knnn
 */

#ifndef UART_ESP_H_
#define UART_ESP_H_

#include "main.h"

typedef struct __attribute__((packed)){
  uint8_t Header[2];

  union {
    uint8_t moveBtnByte;
    struct {
      uint8_t move1 : 1;
      uint8_t move2 : 1;
      uint8_t move3 : 1;
      uint8_t move4 : 1;
      uint8_t res1 : 2;
      uint8_t set1 : 1;
      uint8_t set2 : 1;
    } moveBtnBit;
  };

  union {
    uint8_t attackBtnByte;
    struct {
      uint8_t attack1 : 1;
      uint8_t attack2 : 1;
      uint8_t attack3 : 1;
      uint8_t attack4 : 1;
      uint8_t res1 : 4;
    } attackBtnBit;
  };

  int8_t stickValue[4];  //joyL_X,joyL_Y ,joyR_X,joyR_Y

} ControllerData;

extern ControllerData Str_PS2;


extern uint32_t UART_TIMEOUT_MS;
extern uint32_t last_uart_data_time;
extern uint8_t uart_resetting;

extern uint8_t Status_UART;

uint8_t UART_Runner(UART_HandleTypeDef *UART);

#endif /* UART_ESP_H_ */
