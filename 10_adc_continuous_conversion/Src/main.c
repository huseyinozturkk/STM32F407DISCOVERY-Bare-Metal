#include "adc.h"

uint32_t adc_val;

int main()
{

	pa1_adc_init();

	// continuous conv. olduğu için bir defa başlatılması yeterli
	start_conversion();

	while(1)
	{


		adc_val = adc_read();


		// delay
		for (int i = 0; i < 100000; i++)
		{
			__asm("NOP");
		}

	}
}
