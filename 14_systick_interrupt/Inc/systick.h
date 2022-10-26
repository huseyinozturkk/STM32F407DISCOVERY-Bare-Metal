/*
 * systick.h
 *
 *  Created on: Oct 27, 2022
 *      Author: Hüseyin Öztürk
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

void init_systick(void);
void systick_delay_ms(int delay_ms);
void SysTick_Handler(void);

#endif /* SYSTICK_H_ */
