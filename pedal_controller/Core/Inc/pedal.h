/*
 * pedal.h
 *
 *  Created on: Oct 26, 2026
 *      Author: eagle
 */

#ifndef INC_PEDAL_H_
#define INC_PEDAL_H_

#include <stdint.h>

#define NUM_CH 3
#define NUM_PRESETS 2
#define VAL_MAX 4095

typedef enum { EV_NONE, EV_B1_SHORT, EV_B1_LONG, EV_B2_LONG } ev_t;
typedef enum { M_LIVE, M_P1, M_P2 } pmode_t;
typedef enum { PWR_OFF, PWR_ON, PWR_DIM } pwr_t;

typedef struct {
	uint16_t v[NUM_CH];
}preset_t;

#endif /* INC_PEDAL_H_ */
