
/*
*******************************************************
*******************************************************

This code is for the nRF5340, an impressive wireless System-on-Chip (SoC) developed by Nordic Semiconductor.
It features 1 MB of Flash memory and 512 KB of RAM.


By: Rasheed Dadoush

Context: Created during the first year of the Robotics Engineering program at Mälardalen University.
Course Name: Programming and Development of Embedded Systems
Program: Master’s Program in Robotics
University: Mälardalen University

*******************************************************
*******************************************************
*/

#include "dva270.h"

static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0); // Behövs där finns instance i main.c eller grupp.c
uint8_t uarte_buffer;

int main(void)
{
	uint8_t end[] = "The program is close.";

	// Vi kör med default settings och anger våra TX och RX pinnar:
	const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
	// Initierar UARTE:
	nrfx_err_t errr = nrfx_uarte_init(&instance, &config, NULL);
	if (errr != 0)
	{
		// Hantera det, om ni känner att ni behöver det.
	}

	start_gpio();

	start_app();
	
	nrfx_systick_delay_ms(500);

	uarte_write(end, sizeof(end));
}
