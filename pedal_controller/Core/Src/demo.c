/*
 * demo.c
 *
 *  Created on: Oct 27, 2026
 *      Author: eagle
 */

#include "main.h"
#include "demo.h"
#include "pedal.h"
#include "digipot.h"
#include "leds.h"
#include "buttons.h"

// test value for the 3 pots in each: live, preset 1, preset 2
static const preset_t vals[3] = {
		{{2048, 2048, 2048}},
		{{1024, 2048, 3072}},
		{{4095, 0, 2048}},
};

static pmode_t mode = M_LIVE;
static pwr_t pwr = PWR_ON;

static void wait(uint32_t ms)
{
	uint32_t t = HAL_GetTick();
	while (HAL_GetTick() - t < ms) leds_tick();
}

static void load(pmode_t m)	// send the values of mode m to all 3 pots
{
	uint8_t ch;
	for (ch = 1; ch <= NUM_CH; ch++) digipot_set(ch, vals[m].v[ch - 1]);
}

void demo_init(void)
{
	leds_init();
	// leds self-test: show every led state once
	leds_set(PWR_ON, M_P1, 0); wait(1000);
	leds_set(PWR_ON, M_P2, 1); wait(1000);
	leds_saved();
	leds_set(PWR_ON, M_P2, 0); wait(1000);
	leds_set(PWR_DIM, M_LIVE, 0); wait(1000);

	// start in live
	load(mode);	// mode = M_LIVE. vals[0] = 2048, 2048, 2048. that is 11 80 three times for each pot
	leds_set(pwr, mode, 0);	// pwr = PWR_ON. green led only
}

void demo_tick(void)
{
	ev_t ev = button_event();	// decides short or long

	if (ev == EV_B1_SHORT)	// button released before 1s. standby on/off
	{
		if (pwr == PWR_ON) pwr = PWR_DIM;	// on to standby
		else pwr = PWR_ON;					// standby to on
		digipot_enable(pwr == PWR_ON);
		leds_set(pwr, mode, 0);
	}
	else if (ev == EV_B1_LONG && pwr == PWR_ON)	//next mode
	{
		if (mode == M_LIVE) mode = M_P1;
		else if (mode == M_P1) mode = M_P2;
		else mode = M_LIVE;
		load(mode);
		leds_set(pwr, mode, 0);
	}
	leds_tick();
}

