#include "systick.h"
#include "stm32f407xx.h"

#define PIN12		(1U << 12)
#define PIN13		(1U << 13)
#define PIN14		(1U << 14)
#define PIN15		(1U << 15)


void init_built_in_leds(void);
void leds_toggle(void);

int main()
{
	int delay = 100;

	init_systick();
	init_built_in_leds();

	while (1)
	{
		systick_delay_ms(delay);
		leds_toggle();

		delay = delay >= 1000 ? 100 : delay + 100;
	}
}

void init_built_in_leds(void)
{
	// en clock access for gpiod
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

	// clear gpiod moder
	GPIOD->MODER &= 0x00;

	// set output built in leds
	// D12
	GPIOD->MODER |= (1U << 24);
	GPIOD->MODER &= ~(1U << 25);
	// 13
	GPIOD->MODER |= (1U << 26);
	GPIOD->MODER &= ~(1U << 27);
	// 14
	GPIOD->MODER |= (1U << 28);
	GPIOD->MODER &= ~(1U << 29);
	// 15
	GPIOD->MODER |= (1U << 30);
	GPIOD->MODER &= ~(1U << 31);

}

void leds_toggle(void)
{
	GPIOD->ODR ^= PIN12 | PIN13 | PIN14 | PIN15;
}
