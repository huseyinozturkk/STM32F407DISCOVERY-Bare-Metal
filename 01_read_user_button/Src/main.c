#define PERIPH_BASE 		0x40000000UL
#define AHB1PERIPH_BASE 	(PERIPH_BASE + 0x20000UL)							// 0x4002 0000

#define GPIOA_BASE			(AHB1PERIPH_BASE + 0x00UL)							// 0x4002 0000
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + 0x00UL))	// 0x4002 0000
#define GPIOA_ID_R			(*(volatile unsigned int *)(GPIOA_BASE + 0x10L))	// 0x4002 0010

#define GPIOD_BASE			(AHB1PERIPH_BASE + 0xC00UL)							// 0x4002 0C00
#define GPIOD_MODE_R		(*(volatile unsigned int *)(GPIOD_BASE + 0x00UL))	// 0x4002 0C00
#define GPIOD_OD_R			(*(volatile unsigned int *)(GPIOD_BASE + 0x14UL))	// 0x4002 0C14

#define RCC_BASE 			(AHB1PERIPH_BASE + 0x3800UL)						// 0x4002 3800
#define RCC_AHB1EN_R		(*(volatile unsigned int *)(RCC_BASE + 0x30UL))		// 0x4002 3830
#define RCC_GPIOA_EN		(1U << 0)
#define RCC_GPIOD_EN 		(1U << 3)

#define PIN0				(1U << 0)
#define PIN12				(1U << 12)
#define PIN13				(1U << 13)
#define PIN14				(1U << 14)
#define PIN15				(1U << 15)

#define DELAY				100000

int main()
{
	// clocklar aktif edilir.
	RCC_AHB1EN_R |= RCC_GPIOD_EN | RCC_GPIOA_EN;

	// portlar temizlenir.
	GPIOA_MODE_R &= 0xA8000000;
	GPIOD_MODE_R &= 0x0;

	// kart üzerindeki A0 portuna bağlı buton giriş olarak ayarlanır.
	// 0
	GPIOA_MODE_R &= ~(1U << 0);
	GPIOA_MODE_R &= ~(1U << 1);


	// kart üzerindeki D12-15 portlarına bağlı ledler çıkış olarak ayarlanır.
	// 12
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

	int i = 0;

	while(1)
	{
		// Bit maskeleme ile PIN0 durumunu belirten bit okunarak kontrol sağlanır.
		while ((GPIOA_ID_R & PIN0))
		{
			if ((GPIOA_ID_R & PIN0) == 0)
			{
				i++;
				GPIOD_OD_R ^= (1U << (12 + (i % 4)));
				break;
			}
		}


	}

	return 0;
}
