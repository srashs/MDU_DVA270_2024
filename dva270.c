
#include "dva270.h"

#define _CRT_SECURE_NO_WARNINGS

static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0); // Den behövs i .h filen

// Skapar en driver instance för UARTE:

void uarte_write(uint8_t *data, uint8_t length)
{
	nrfx_uarte_tx(&instance, data, length, 0);
	while(nrfx_uarte_tx_in_progress(&instance));
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
	uint8_t test[]="\n\rThis is a test\n\r";
	uarte_write(test,sizeof(test));
}
