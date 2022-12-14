#include "stm32f407xx.h"

#define GPIOD_EN	(1U << 3)
#define GPIOA_EN 	(1U << 0)

#define PIN0		(1U << 0)
#define PIN12		(1U << 12)
#define PIN13		(1U << 13)
#define PIN14		(1U << 14)
#define PIN15		(1U << 15)

#define BUTTON 		PIN0
#define LED1		PIN12
#define LED2		PIN13
#define LED3		PIN14
#define LED4		PIN15

#define DELAY 		100000

int main()
{
	// Clocklar aktif edilir.
	RCC->AHB1ENR |= GPIOD_EN | GPIOA_EN;

	// D portu temizlenir.
	GPIOD->MODER &= 0x0;
	GPIOA->MODER &= 0xA8000000;

	// BUTON giriş olarak ayarlanır.
	// A0
	GPIOA->MODER &= ~(1U << 0);
	GPIOA->MODER &= ~(1U << 1);

	// LEDler çıkış olarak ayarlanır.
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

	while(1)
	{
		if (GPIOA->IDR & BUTTON)
		{
			GPIOD->BSRR = PIN12 | PIN13 | PIN14 | PIN15;
		}
		else
		{

			//GPIOD->BSRR = (1U << 28) | (1U << 29) | (1U << 30) | (1U << 31);
			//GPIOD->BSRR = LED1 << 16 | LED2 << 16 | LED3 << 16 | LED4 << 16;
			GPIOD->BSRR = (LED1 | LED2 | LED3 | LED4) << 16;
		}

	}
	return 0;
}
