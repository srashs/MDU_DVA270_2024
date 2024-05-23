#ifndef LIST_H
#define LIST_H

#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrfx_glue.h>


#include <nrfx_uarte.h>		// TX RX read write

#include <nrf_gpio.h>		// LEDs

#include <nrfx_systick.h>	

#include <nrfx_rtc.h> //nrfx_rtc.c i main + NRFX_RTC_ENABLED / 0 to 1

#include <assert.h>

#define CLEAR_SCREEN "\033c"

#define size_input_text 100


// definerar vilka pinnar som kommer användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22


// definerar vilka pinnar som kommer användas (LED):
#define LED1 28
#define LED2 29
#define LED3 30
#define LED4 31

#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9


#define LED_OFF 1
#define LED_ON 0

//static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);



// functions
void uarte_write(uint8_t *data, uint8_t length);
void read_string(uint8_t input[]);
uint32_t read_int(uint8_t input[]);
void start_gpio();
void newline(void);
void test_text(void);
void start_app();


#endif