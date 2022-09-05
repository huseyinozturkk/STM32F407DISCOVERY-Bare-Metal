#define PERIPH_BASE 		0x40000000UL
#define AHB1PERIPH_BASE 	(PERIPH_BASE + 0x20000UL)							// 0x4002 0000

#define GPIOD_BASE			(AHB1PERIPH_BASE + 0xC00UL)							// 0x4002 0C00
#define GPIOD_MODE_R		(*(volatile unsigned int *)(GPIOD_BASE + 0x00UL))	// 0x4002 0C00
#define GPIOD_OD_R			(*(volatile unsigned int *)(GPIOD_BASE + 0x14UL))	// 0x4002 0C14

#define RCC_BASE 			(AHB1PERIPH_BASE + 0x3800UL)						// 0x4002 3800
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + 0x30UL))		// 0x4002 3830
#define RCC_GPIOD_EN 		(1U << 3)

#define PIN12				(1U << 12)
#define PIN13				(1U << 13)
#define PIN14				(1U << 14)
#define PIN15				(1U << 15)

#define DELAY				100000
int main()
{
	// D portu için clock aktif edilir.
	RCC_AHB1EN_R |= RCC_GPIOD_EN;

	// D portu temizlenir
	GPIOD_MODE_R &= 0x0;

	// D12 çıkış olarak ayarlanır
	GPIOD_MODE_R |= (1U << 24);
	GPIOD_MODE_R &= ~(1U << 25);
	// 13
	GPIOD_MODE_R |= (1U << 26);
	GPIOD_MODE_R &= ~(1U << 27);
	// 14
	GPIOD_MODE_R |= (1U << 28);
	GPIOD_MODE_R &= ~(1U << 29);
	// 15
	GPIOD_MODE_R |= (1U << 30);
	GPIOD_MODE_R &= ~(1U << 31);

	while(1)
	{
		GPIOD_OD_R ^= PIN12;
		GPIOD_OD_R ^= PIN13;
		GPIOD_OD_R ^= PIN14;
		GPIOD_OD_R ^= PIN15;

		for(int i = 0; i < DELAY; i++);
	}

	return 0;
}
