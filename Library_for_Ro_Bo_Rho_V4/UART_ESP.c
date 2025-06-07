/*
 * UART_ESP.c
 *
 *  Created on: May 6, 2025
 *      Author: Knnn
 */
#include "UART_ESP.h"

uint32_t UART_TIMEOUT_MS  = 500;
uint32_t last_uart_data_time = 0;
uint8_t uart_resetting = 0;

uint8_t Status_UART;

UART_HandleTypeDef *UART;

uint8_t UART_Runner(UART_HandleTypeDef *UART){
	if (((uwTick - last_uart_data_time) < UART_TIMEOUT_MS)
			&& (Str_PS2.Header[0] == 'R') && (Str_PS2.Header[1] == 'B')) {
		Status_UART = 1;

		Str_PS2.Header[0] = 0;
		Str_PS2.Header[1] = 0;
	} else {
		if (!uart_resetting && ((uwTick - last_uart_data_time) > UART_TIMEOUT_MS)) {
			uart_resetting = 1;

			HAL_UART_DeInit(UART);
			HAL_Delay(10);

			UART->Instance = USART2;
			UART->Init.BaudRate = 115200;
			UART->Init.WordLength = UART_WORDLENGTH_8B;
			UART->Init.StopBits = UART_STOPBITS_1;
			UART->Init.Parity = UART_PARITY_NONE;
			UART->Init.Mode = UART_MODE_TX_RX;
			UART->Init.HwFlowCtl = UART_HWCONTROL_NONE;
			UART->Init.OverSampling = UART_OVERSAMPLING_16;
			if (HAL_UART_Init(UART) != HAL_OK) {
				Error_Handler();
			}

			HAL_UART_Receive_IT(UART, (uint8_t*) &Str_PS2, sizeof(Str_PS2));

			memset(&Str_PS2, 0, sizeof(Str_PS2));

			Status_UART = 0;
		}
	}
	return Status_UART;
}
