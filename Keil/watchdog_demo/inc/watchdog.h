#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "TM4C123GH6PM.h"
#include <stdlib.h>

#define W0                      1U
#define RESEN                   1U << 1
#define INTEN                   1U
#define WDT0                    1U << 18
#define WDT_LOADVALUE           0xFF0000
#define GPIO_PORTF              1U << 5
#define LED_RED                 1U << 1
#define LED_GREEN               1U << 3

void watchdog_init(void);
void gpio_init(void);
void WDT0_Handler(void);
void enable_watchdog0_interrupt(void);

#if defined(MILLISECONDS)
#define CONSTANT    1000
void delay_milliseconds(unsigned int);
#elif defined(SECONDS)
#define CONSTANT        1000000
void delay_seconds(unsigned int);
#endif

#endif
