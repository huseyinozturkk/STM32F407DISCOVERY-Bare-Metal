/*
 * systick.c
 *
 *  Created on: Oct 27, 2022
 *      Author: Hüseyin Öztürk
 */

#include "stm32f407xx.h"

#define SYSTEM_FREQ			( 8000000 )

#define SYSTICK_LOAD_VAL	( SYSTEM_FREQ / 1000 ) // 1 ms için 1000 ile bölünür
#define CTRL_EN				( 1U << 0 )
#define CTRL_CLKSRC			( 1U << 2 ) // system clock -> 1, external clock ->0
#define CTRL_CNTFLAG		( 1U << 16 )

void init_systick(void)
{
	// clear cntrl reg
	SysTick->CTRL = 0x00;

	// load val
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// clear systick current value reg
	SysTick->VAL = 0;

	// select clock source
	SysTick->CTRL |= CTRL_CLKSRC;

	// en systick
	SysTick->CTRL |= CTRL_EN;
}

void systick_delay_ms(int delay_ms)
{
	for (int i = 0; i < delay_ms; i++)
	{
		while ((SysTick->CTRL & CTRL_CNTFLAG) == 0){}
	}
}
