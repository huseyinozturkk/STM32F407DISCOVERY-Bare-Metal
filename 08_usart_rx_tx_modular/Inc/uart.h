/*
 * uart.h
 *
 *  Created on: 22 Eyl 2022
 *      Author: blue
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f407xx.h"
#include <stdint.h>

void usart2_tx_rx_init(void);
void usart2_write(uint8_t ch);
void usart2_test(uint8_t *pMsg, uint8_t msgLen);



#endif /* UART_H_ */
