#include <stdint.h>
#include <string.h>

#include "stm32f407xx.h"

// USART2 (APB1) TX-> PA2  RX-> PA3
#define USART2_EN		(1U << 17)
#define CR1_TE			(1U << 3)	// UART Transmit en
#define CR1_UA			(1U << 13)	// UART UART en
#define SR_TXE			(1U << 6)

// GPIOA (AHB1)
#define GPIOA_EN		(1U << 0)

#define SYS_FREQ 		((uint32_t)16000000)	// internal high speed osc
#define APB1_CLK		SYS_FREQ

#define UART_BAUDRATE 	((uint32_t)115200)

void usart2_tx_init(void);
void usart2_write(uint8_t ch);
void usart2_test(uint8_t *pMsg, uint8_t msgLen);

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t baudRate);
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t baudRate);

int main() {

	//clock_init();
	//set_clock_168();

	usart2_tx_init();

	// initden sonra delay olmalı, direkt iletim yaparsa ilk byte hatalı gidiyor
	// ayrıca sistem baslangıcınca stm kendi sacma bir sey basıyor
	for(int i = 0; i < 1000000; i++);
	usart2_write('\n');

	uint8_t msg[30] = "ESENLIKLER DUNYA\n";
	usart2_test((uint8_t*)msg, strlen(msg));

	for(int i = 0; i < 1000000; i++);

	while(1) {
		usart2_write('H');
		for(int i = 0; i < 100000; i++);
		usart2_write('U');
		for(int i = 0; i < 100000; i++);
		usart2_write('S');
		for(int i = 0; i < 100000; i++);
		usart2_write('E');
		for(int i = 0; i < 100000; i++);
		usart2_write('Y');
		for(int i = 0; i < 100000; i++);
		usart2_write('I');
		for(int i = 0; i < 100000; i++);
		usart2_write('N');
		for(int i = 0; i < 100000; i++);
		usart2_write('\n');

	}
}


void usart2_tx_init(void) {
	// ----- gpio config -----
		// gpio clock
		RCC->AHB1ENR |= GPIOA_EN;
		// set gpio AF mode
		GPIOA->MODER = 0xA8000000;  // reset

		GPIOA->MODER |= (0x2 << 4); // 0b01 AF - alternate func mod
		// set gpio speed
		GPIOA->OSPEEDR = 0x0C000000;  // reset
		GPIOA->OSPEEDR |= (0x2 << 4); // 0b10

		// set gpio AF type USART2 - AF7 - b0111
		GPIOA->AFR[0] |= (0x7 << 8); // pin A2 - tx
		//GPIOA->AFR[0] |= (0x7 << 12); // 	pin A3- rx

		// ----- uart config -----
		// uart clock en
		RCC->APB1ENR |= USART2_EN;
		// uart baudrate
		uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);
		// uart transfer direction
		USART2->CR1 = 0x0; 	// reset
		USART2->CR1 |= CR1_TE; // transmit en
		// en uart
		USART2->CR1 |= CR1_UA;	// uart en

}

void usart2_write(uint8_t ch) {
	// is transmit data reg empty
	while(!(USART2->SR & SR_TXE)) {}
	// write data to tx data reg
	USART2->DR = (ch & 0xFF);
}

void usart2_test(uint8_t *pMsg, uint8_t msgLen) {

	for (uint8_t i = 0; i < msgLen; i++) {
		// wait for TXE
	    while(!(USART2->SR & SR_TXE));

	    // send
	    USART2->DR = (*pMsg++ & 0xFF);
	}
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t baudRate) {
	USARTx->BRR = compute_uart_bd(PeriphClk, baudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t baudRate) {
	return ((PeriphClk + (baudRate / 2U))/baudRate);
}

