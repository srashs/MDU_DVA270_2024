
#include "dva270.h"

#define _CRT_SECURE_NO_WARNINGS

static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0); // Den behövs i .h filen

// Skapar en driver instance för UARTE:

void uarte_write(uint8_t *data, uint8_t length)
{
	nrfx_uarte_tx(&instance, data, length, 0);
	while (nrfx_uarte_tx_in_progress(&instance))
		;
}

void read_string(uint8_t input[])
{
	uint8_t uarte_buffer;
	memset(input, '\0', sizeof(input));
	uint32_t i = 0;
	do
	{
		nrfx_uarte_rx(&instance, &uarte_buffer, sizeof(uarte_buffer));
		input[i] = uarte_buffer;
		i++;
	} while (input[i - 1] != '\r');
	input[i - 1] = NULL;
}

uint32_t read_int(uint8_t input[])
{
	int i;
	i = atoi(input);
	return i;
}

void start_gpio()
{
	// förbereder alla LEDs och alla knappar för användning.

	nrfx_systick_init();

	nrf_gpio_cfg_output(LED1);
	nrf_gpio_cfg_output(LED2);
	nrf_gpio_cfg_output(LED3);
	nrf_gpio_cfg_output(LED4);

	nrf_gpio_pin_write(LED1, LED_OFF);
	nrf_gpio_pin_write(LED2, LED_OFF);
	nrf_gpio_pin_write(LED3, LED_OFF);
	nrf_gpio_pin_write(LED4, LED_OFF);

	nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);
}

void newline(void)
{
	uint8_t newline[] = "\n\r";
	nrfx_uarte_tx(&instance, newline, sizeof(newline), 0);
}

void test_text(void)
{
	uint8_t test[] = "\n\rThis is a test\n\r";
	uarte_write(test, sizeof(test));
}

void start_app()
{

	uint8_t input_text[size_input_text];
	memset(input_text, '\0', sizeof(input_text));

	uint8_t run = 1;

	uint8_t msgT1[] = "Skriv 5 to avsluta \n\r Skriv vilken LED ska tändas (Led 1 - Led 4.) \n\r";
	uint8_t msgT2[] = "Skriv hur många sekunder ska den tändas: \n\r";

	// msg som skrivs vid on/off
	uint8_t msg1[] = "Led 1\n\r";
	uint8_t msg2[] = "Led 2\n\r";
	uint8_t msg3[] = "Led 3\n\r";
	uint8_t msg4[] = "Led 4\n\r";
	while (run)
	{

		uint8_t switch_input = 0;

		while (switch_input > 5 || switch_input < 1)
		{
			nrfx_uarte_tx(&instance, msgT1, sizeof(msgT1), 0);
			read_string(input_text);
			switch_input = read_int(input_text);
		}
		if (switch_input == 5) run=0;
		if (switch_input != 5)
		{
			nrfx_uarte_tx(&instance, msgT2, sizeof(msgT2), 0);
			read_string(input_text);
			uint32_t input_time = read_int(input_text);
			uint32_t delay = input_time * 1000; // input time * 1000 because the time is in milliseconds

			switch (switch_input)
			{

			case 1:
				nrfx_uarte_tx(&instance, msg1, sizeof(msg1), 0);
				while (delay > 10)
				{

					nrf_gpio_pin_toggle(LED1);
					nrfx_systick_delay_ms(delay);
					nrf_gpio_pin_toggle(LED1);
					nrfx_systick_delay_ms(delay);
					delay = delay / 2;
					switch_input = 0;
				}
				break;

			case 2:
				nrfx_uarte_tx(&instance, msg2, sizeof(msg2), 0);
				while (delay > 10)
				{

					nrf_gpio_pin_toggle(LED2);
					nrfx_systick_delay_ms(delay);
					nrf_gpio_pin_toggle(LED2);
					nrfx_systick_delay_ms(delay);
					delay = delay / 2;
					switch_input = 0;
				}
				break;

			case 3:
				nrfx_uarte_tx(&instance, msg3, sizeof(msg3), 0);
				while (delay > 10)
				{

					nrf_gpio_pin_toggle(LED3);
					nrfx_systick_delay_ms(delay);
					nrf_gpio_pin_toggle(LED3);
					nrfx_systick_delay_ms(delay);
					delay = delay / 2;
					switch_input = 0;
				}
				break;

			case 4:
				nrfx_uarte_tx(&instance, msg4, sizeof(msg4), 0);
				while (delay > 10)
				{

					nrf_gpio_pin_toggle(LED4);
					nrfx_systick_delay_ms(delay);
					nrf_gpio_pin_toggle(LED4);
					nrfx_systick_delay_ms(delay);
					delay = delay / 2;
					switch_input = 0;
				}
				break;

			default:
				break;
			}
		}
	}
}