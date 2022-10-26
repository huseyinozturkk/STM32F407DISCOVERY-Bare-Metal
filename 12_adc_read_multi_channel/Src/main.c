#include "adc.h"

#define ADC_CH1 	( 1 )
#define ADC_CH2 	( 2 )
#define ADC_CH3 	( 3 )

int main()
{
	uint32_t adc_val_ch1;
	uint32_t adc_val_ch2;
	uint32_t adc_val_ch3;

	adc_init_multi_ch();



	while(1)
	{
		// read ch1
		adc_start_ch(ADC_CH1);
		adc_val_ch1 = adc_read();

		// read ch2
		adc_start_ch(ADC_CH2);
		adc_val_ch2 = adc_read();

		// read ch3
		adc_start_ch(ADC_CH3);
		adc_val_ch3 = adc_read();
	}
}
