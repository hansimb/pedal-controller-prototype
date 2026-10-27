/*
 * leds.h
 *
 *  Created on: Oct 26, 2026
 *      Author: eagle
 */

#ifndef INC_LEDS_H_
#define INC_LEDS_H_

#include "pedal.h"

void leds_init(void);
void leds_set(pwr_t power, pmode_t preset, uint8_t edited);
void leds_saved(void);
void leds_tick(void);


#endif /* INC_LEDS_H_ */
