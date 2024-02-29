#ifndef GENERATE_DELAY_H
#define GENERATE_DELAY_H

#include "TM4C123GH6PM.h"
#include <stdbool.h>

#define R0                      1U
#define TAEN                    1U
#define CFG_16_BIT              0x04
#define ONE_SHOT                0x01
#define TACDIR                  1U << 4
#define TATOIM                  1U
#define TATOCINT                1U
#define TATOMIS                 1U
#define GPIO_PORTF              1U << 5
#define LED_GREEN               1U << 3

#if defined(MILLISECONDS)
#define MILLISECONDS_CONSTANT   4.096
#define MILLISECONDS_VALUE      100

void set_milliseconds(unsigned int);

static unsigned volatile int miliseconds = 0;
#endif

#elif defined(SECONDS)
#define SECONDS_PRESCALE        245
#define SECONDS_CONSTANT        1.00352
#define SECONDS_VALUE           30

void set_seconds(unsigned int);

static unsigned volatile int seconds = 0;
#endif

static unsigned volatile int handler_counter = 0;
static bool is_indicator_enabled             = false;

void timer_init(void);
void use_indicator(void);				//green LED stays ON for specified time
void disable_indicator(void);
void disable_timer(void);				//stops timer from counting
void TIMER0A_Handler(void);
void HardFault_Handler(void);

#endif
