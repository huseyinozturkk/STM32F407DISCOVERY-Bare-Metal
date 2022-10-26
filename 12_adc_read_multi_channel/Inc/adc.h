/*
 * adc.h
 *
 *  Created on: 26 Eki 2022
 *      Author: Hüseyin Öztürk
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init_multi_ch(void);
void adc_start_ch(uint8_t ch);
uint32_t adc_read(void);

#endif /* ADC_H_ */
