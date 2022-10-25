/*
 * internal_temp_sensor.h
 *
 *  Created on: 25 Eki 2022
 *      Author: Hüseyin Öztürk
 */

#ifndef INTERNAL_TEMP_SENSOR_H_
#define INTERNAL_TEMP_SENSOR_H_

#include <stdint.h>

void internal_temp_sens_init(void);
uint32_t read_adc(void);
void start_temp_sensor(void);

#endif /* INTERNAL_TEMP_SENSOR_H_ */
