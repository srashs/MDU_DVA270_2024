
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

	uint8_t input_text[size_input_text];
	memset(input_text, '\0', sizeof(input_text));

	uint8_t run = 1;
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

	char CLEAR[] = CLEAR_SCREEN;
	uint8_t please [] = "Please enter a number:" ;
	while (run)
	{

		int switch_input = 0;
		uarte_write(please, sizeof(please));
		read_string(input_text);
		switch_input = read_int(input_text);

		switch (switch_input)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			test_text();
			break;
		case 5:
			run = 0; // exit
			break;
		default:
			break;
		}
		uarte_buffer = 0;

		nrfx_systick_delay_ms(500);
	}

	uarte_write(end, sizeof(end));
}
