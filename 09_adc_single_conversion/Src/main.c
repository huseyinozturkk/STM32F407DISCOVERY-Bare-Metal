#include "adc.h"

uint32_t adc_val;

int main()
{

	pa1_adc_init();

	while(1)
	{

		// single conv. olduğu için adc okuması yapmadan evvel conv. için başlatma gerekli
		start_conversion();
		adc_val = adc_read();


		// delay
		for (int i = 0; i < 100000; i++)
		{
			__asm("NOP");
		}

	}
}
