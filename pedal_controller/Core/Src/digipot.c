/*
 * digipot.c
 *
 *  Created on: Oct 25, 2026
 *      Author: eagle
 */

#include "main.h"
#include "digipot.h"

extern SPI_HandleTypeDef hspi2;

static GPIO_TypeDef *const port[3] = {DigiPot1_GPIO_Port, DigiPot2_GPIO_Port, DigiPot3_GPIO_Port};
static const uint16_t pin[3] = {DigiPot1_Pin, DigiPot2_Pin, DigiPot3_Pin};

void digipot_set(uint8_t ch, uint16_t val)
{
	uint8_t tx[2];

	if (ch < 1 || ch > 3)
		return;
	if (val > 4095)
		val = 4095;
	tx[0] = 0x11;
	tx[1] = val >> 4;
	HAL_GPIO_WritePin(port[ch - 1], pin[ch - 1], GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, tx, 2, 10);
	HAL_GPIO_WritePin(port[ch - 1], pin[ch - 1], GPIO_PIN_SET);

}
