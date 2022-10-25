/*
 * internal_temp_sensor.c
 *
 *  Created on: 25 Eki 2022
 *      Author: Hüseyin Öztürk
 */

//For the STM32F40x and STM32F41x devices,
//the temperature sensor is internally
//connected to channel ADC1_IN16.

// ADC_CR1 reg Bits 4:0 AWDCH[4:0] for ch selection
// 10000: ADC analog input Channel16

#include "stm32f407xx.h"
#include "internal_temp_sensor.h"

#define ADC1_EOC	( 1U << 1 )

void internal_temp_sens_init(void)
{
	// ADC en clock access to temp. sens.
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	// adc ch select
	// set conv sequence
	ADC1->SQR3 = 0x10;
	// set conv len
	ADC1->SQR1 = 0x00;

	// set TSVREFE bit in the ADC_CCRreg
	ADC->CCR |= ADC_CCR_TSVREFE;

	// en adc
	ADC1->CR2 |= ADC_CR2_ADON;

	// delay
	for (int i = 0; i < 100000; i++){}
}

void start_temp_sensor(void)
{
	// set continuous conv. mode
	ADC1->CR2 |= ADC_CR2_CONT;

	// start adc conv.
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t read_adc(void)
{
	while(!(ADC1->SR & ADC1_EOC)){}

	return ADC1->DR;

}
