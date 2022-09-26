#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "stm32f407xx.h"
#include "uart.h"





int main() {

	usart2_tx_init();

	// initden sonra delay olmalı, direkt iletim yaparsa ilk byte hatalı gidiyor
	// ayrıca sistem baslangıcınca stm kendi sacma bir sey basıyor
	for(int i = 0; i < 1000000; i++);
	usart2_write('\n');

	uint8_t msg[30] = "ESENLIKLER DUNYA\n";
	usart2_test((uint8_t*)msg, strlen(msg));

	for(int i = 0; i < 1000000; i++);

	while(1) {
		printf("HUSEYIN OZTURK\n\r");

	}
}




