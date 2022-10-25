/*
 * adc.c
 *
 *  Created on: 25 Eki 2022
 *      Author: Hüseyin Öztürk
 */
#include "stm32f407xx.h"
#include "adc.h"

#define ADC_CH1		( 1U << 0 )
#define ADC1_EOC	( 1U << 1 )

// PA1 ADC123_IN1
void pa1_adc_init()
{

	// en clock access to gpioa
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// reset gpio moder for gpioa
	GPIOA->MODER &= 0x0;
	GPIOA->MODER |= 0xA8000000;

	// set pa1 to analog
//	GPIOA->MODER |= (1U << 2);
//	GPIOA->MODER |= (1U << 3);

	GPIOA->MODER |= (0x3 << 2);

	// ADC
	// en clock access to adc1
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

	// config adc params.
	// sequence -> rank / bir nevi öncelik

	// tek kanal okuma yaptığımız için SQ1
	// conversion sequence start
	ADC1->SQR3 = ADC_CH1;

	// tek kanal olduğu için tüm registerı 0 layarak 1 conversion ayarlanır
	// conversion sequence len
	ADC1->SQR1 = 0x00;

	// en adc
	ADC1->CR2 |= ADC_CR2_ADON;

}

void start_conversion(void)
{
	// continuous conv. start
	ADC1->CR2 |= ADC_CR2_CONT;

	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void)
{
	// wait for conv. cmplt
	while(!(ADC1->SR & ADC1_EOC)){}

	// read data
	return ADC1->DR;
}
