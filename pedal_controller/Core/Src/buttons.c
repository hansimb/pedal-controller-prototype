/*
 * buttons.c
 *
 *  Created on: Oct 27, 2026
 *      Author: eagle
 */

#include "main.h"
#include "buttons.h"

#define DEBOUNCE_MS 20
#define SHORT_MS 1000
#define LONG_MS 3000

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;
	ev_t short_ev;
	ev_t long_ev;

	uint8_t raw;	// last pin reading
	uint8_t state;	// debounced state, 1 = pressed
	uint8_t done;	// long press already sent
	uint32_t t_raw;	// time of last pin change
	uint32_t t_down; // time of debounced press
}btn_t;

static btn_t b1 = {.port = B1_GPIO_Port, .pin = B1_Pin, .short_ev = EV_B1_SHORT, .long_ev = EV_B1_LONG};

static ev_t check(btn_t *b)
{
	uint32_t now = HAL_GetTick();
	uint8_t raw = HAL_GPIO_ReadPin(b->port, b->pin) == GPIO_PIN_SET;

	if (raw != b->raw)	// pin changed: restart the debounce timer
	{
		b->raw = raw;
		b->t_raw = now;
	}
	if (raw != b->state && now - b->t_raw >= DEBOUNCE_MS)	// steady for 20ms: accept it
	{
		b->state = raw;
		if (raw)	// pressed
			{
			b->t_down = now;
			b->done = 0;
			}
			else if (now - b->t_down < SHORT_MS)	// released before 1 s
			{
			return b->short_ev;
			}
	}

	if (b->state && !b->done && now - b->t_down >= LONG_MS)	// held 3 seconds
	{
		b->done = 1;
		return b->long_ev;
	}
	return EV_NONE;

}

ev_t button_event(void)
{
	return check(&b1);
}
