/*
 * leds.c
 *
 *  Created on: Oct 26, 2026
 *      Author: eagle
 */


#include "main.h"
#include "leds.h"

// Driver for the four board LEDs: green PD12 (PWM on TIM4), orange pd13, red pd 14, blue pd15

extern TIM_HandleTypeDef htim4; // TIM4 handle from main.c

#define FULL 1000 // green fully on: CCR above the counter period 999
#define DIM 50    // green in standby: 5% of the time on
#define BLINK_MS 100 // blue state to return to after the save signla

static uint8_t blinks; // blue changes left in the save signal
static uint32_t t0;    // time of the last blue change
static uint8_t edit;	// blue state to return to after the save signal

//switch one plain LED on or off
static void led(GPIO_TypeDef *port, uint16_t pin, uint8_t on)
{
	if (on)
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

// Start the PWM on the green LED, call once after MX_TIM4_Init()
void leds_init(void)
{
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

// green: power state, orange/red: preset, blue: preset edited and not saved
void leds_set(pwr_t power, pmode_t preset, uint8_t edited)
{
	uint16_t ccr = 0;

	if (power == PWR_ON)
		ccr = FULL;
	else if (power == PWR_DIM)
		ccr = DIM;
	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, ccr);

	if (power != PWR_ON)	//standby
	{
		preset = M_LIVE;
		edited = 0;
	}
	led(LD3_GPIO_Port, LD3_Pin, preset == M_P1);
	led(LD5_GPIO_Port, LD5_Pin, preset == M_P2);
	edit = edited;

	if (blinks == 0)	// during the saved signal, blue is busy
		led(LD6_GPIO_Port, LD6_Pin, edited);
}

// start the save signal: three fast blue blinks
void leds_saved(void)
{
	led(LD6_GPIO_Port, LD6_Pin, 0);
	blinks = 6;
	t0 = HAL_GetTick();
}

// call often from the main loop: runs the blink timing without stopping the program
void leds_tick(void)
{
	if (blinks == 0)
		return;
	if (HAL_GetTick() - t0 < BLINK_MS)
		return;
	t0 = HAL_GetTick();
	HAL_GPIO_TogglePin(LD6_GPIO_Port, LD6_Pin);
	blinks--;
	if (blinks == 0)	// back to the edited state
		led(LD6_GPIO_Port, LD6_Pin, edit);

}
