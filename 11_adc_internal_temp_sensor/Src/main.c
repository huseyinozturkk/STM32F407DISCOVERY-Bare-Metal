#include "internal_temp_sensor.h"


int main()
{

	uint32_t adc_val;
	float temperature;

	const float avg_slope_v = 2.5;
	const float v_25 = 0.76;


	internal_temp_sens_init();
	start_temp_sensor();

	while(1)
	{
		adc_val = read_adc();

		temperature = (((adc_val * (3.3 / 4095))- v_25) / avg_slope_v) + 25;

		for (int i = 0; i < 10000; i++) {}

	}

}

