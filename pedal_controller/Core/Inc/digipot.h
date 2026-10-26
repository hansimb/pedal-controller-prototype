/*
 * digipot.h
 *
 *  Created on: Oct 25, 2026
 *      Author: Ashish Shrestha
 */

#ifndef INC_DIGIPOT_H_
#define INC_DIGIPOT_H_

#include <stdint.h>

// digital pot driver, see digipot.c
void digipot_set(uint8_t ch, uint16_t val);
void digipot_enable(uint8_t on);

#endif /* INC_DIGIPOT_H_ */
