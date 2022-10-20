#include "stm32f407xx.h"

#define GPIOD_EN	(1U << 3)

#define PIN12				(1U << 12)
#define PIN13				(1U << 13)
#define PIN14				(1U << 14)
#define PIN15				(1U << 15)

#define DELAY 				100000

int main()
{
	RCC->AHB1ENR |= GPIOD_EN;

	// D portu temizlenir
	GPIOD->MODER &= 0x0;

	// D12 çıkış olarak ayarlanır
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

	while(1)
	{
		GPIOD->ODR ^= PIN12;
		GPIOD->ODR ^= PIN13;
		GPIOD->ODR ^= PIN14;
		GPIOD->ODR ^= PIN15;

		for(int i = 0; i < DELAY; i++){}

	}
	return 0;
}




