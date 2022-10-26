/*
/*
 * adc.c
 *
 *  Created on: 26 Eki 2022
 *      Author: Hüseyin Öztürk
 */

#include "stm32f407xx.h"
#include "adc.h"

#define ADC1_EOC	( 1U << 1 )

// PA1 -> ADC1_IN1
// PA2 -> ADC1_IN2
// PA3 -> ADC1_IN3

void adc_init_multi_ch(void)
{
	/* GPIO */
	// en clock access to gpioa
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

	// reset gpio moder reg
	GPIOA->MODER &= 0x0;
	GPIOA->MODER |= 0xA8000000;

	// set pa1 to analog
	GPIOA->MODER |= (0x3 << 2);
	// pa2
	GPIOA->MODER |= (0x3 << 4);
	// pa3
	GPIOA->MODER |= (0x3 << 6);

	/* ADC */
	// en clock access to adc1
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

//	// set channels by rank
//	ADC1->SQR3 |= ( 0x01 & ADC_SQR3_SQ1); // ch1
//	ADC1->SQR3 |= ( 0x02 & ADC_SQR3_SQ2); // ch2
//	ADC1->SQR3 |= ( 0x03 & ADC_SQR3_SQ3); // ch3
//
//	// set conversion len
//	ADC1->SQR1 = 0x02;
//
//	// en scan mode
//	ADC1->CR1 |= ADC_CR1_SCAN;
//
//	// en adc
//	ADC1->CR2 |= ADC_CR2_ADON;
}

void adc_start_ch(uint8_t ch)
{
	// reset ch rank reg
	ADC1->SQR3 = 0x00;

	// set ch rank
	ADC1->SQR3 |= (ch & ADC_SQR3_SQ1);

	// set conv. len
	ADC1->SQR1 = 0x00;

	// en scan mode
	ADC1->CR1 |= ADC_CR1_SCAN;

	// en adc
	ADC1->CR2 |= ADC_CR2_ADON;

//	// set continuous conv. mode
//	ADC1->CR2 |= ADC_CR2_CONT;

	// start adc conv.
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void)
{
	while(!(ADC1->SR & ADC1_EOC)){}

	return ADC1->DR;
}
