/*
 * digipot.c
 *
 *  Created on: Oct 25, 2026
 *      Author: Ashish Shrestha
 */

#include "main.h"
#include "digipot.h"

// driver for the three MCP41010 digipots on SPI2

extern SPI_HandleTypeDef hspi2; // SPI2 handle from main.c

// select pin of each pot: DigiPot1 PD8, DigiPot2 PD9, DigiPot3 PD10
static GPIO_TypeDef *const port[3] = {DigiPot1_GPIO_Port, DigiPot2_GPIO_Port, DigiPot3_GPIO_Port};
static const uint16_t pin[3] = {DigiPot1_Pin, DigiPot2_Pin, DigiPot3_Pin};
static uint8_t last[3];	// last value given to each pot
static uint8_t en = 1; 	// 1 = outputs on, 0 = standny

//one message: select low, send 2 bytes, select high
static void send(uint8_t i, uint8_t cmd, uint8_t data)
{
	uint8_t tx[2] = {cmd, data};

	HAL_GPIO_WritePin(port[i], pin[i], GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi2, tx, 2, 10);
	HAL_GPIO_WritePin(port[i], pin[i], GPIO_PIN_SET); //chip acts when select goes high

}

// set pot ch[1-3] to val (0-4095, same as teh ADC)
void digipot_set(uint8_t ch, uint16_t val)
{

	if (ch < 1 || ch > 3) // no such pot
		return;
	if (val > 4095) // keep it in the 12-bit range
		val = 4095;
	last[ch - 1] = val >> 4; /// remember the value, 12-bit down to 8-bit by dropping the 4 lowest bits

	if (en) // in standby only remember the value
		send(ch - 1, 0x11, last[ch - 1]); // ox11 = write pot 0 (datasheet, sec 5.1)

}

// on = 0: standby, shutdown all pots. 0n = 1: give back the last value
void digipot_enable(uint8_t on)
{
	uint8_t i;

	en = on;
	for (i = 0; i < 3; i++)
	{
		if (on)
			send(i, 0x11, last[i]);  // writing a value ends shutdown
		else
			send(i, 0x21, 0x00); 	// 0x21 = shutdown, data bits not used (datasheet 5.3)
	}
}
