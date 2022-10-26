/*
 * systick.c
 *
 *  Created on: Oct 27, 2022
 *      Author: Hüseyin Öztürk
 */

#include "stm32f407xx.h"

#define SYSTEM_FREQ			( 8000000 )

#define SYSTICK_LOAD_VAL	( SYSTEM_FREQ / 1000 ) // 1 ms için 1000 ile bölünür

// Clock source selection
// 0 -> external clock
// 1 -> system clock 8MHz
#define CLK_SOURCE			( 1U )


static volatile uint32_t systick_count;

void init_systick(void)
{
	// clear cntrl reg
	SysTick->CTRL = 0x00;

	// load val
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// clear systick current value reg
	SysTick->VAL = 0;

	// en irq
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	// select clock source
	SysTick->CTRL |= (CLK_SOURCE << SysTick_CTRL_CLKSOURCE_Pos);

	// en systick
	SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk << SysTick_CTRL_ENABLE_Pos);
}

void systick_delay_ms(int delay_ms)
{
//	// old method
//	for (int i = 0; i < delay_ms; i++)
//	{
//		while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0){}
//	}

	// new method with irq
	uint32_t tick_start;
	tick_start = systick_count;

	while (systick_count - tick_start < delay_ms){}
}

void SysTick_Handler(void)
{
	systick_count++;
}
