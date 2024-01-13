#ifndef __WATCHDOG_H__
#define __WATCHDOG_H__

#include "TM4C123GH6PM.h"
#include <stdlib.h>

#define W0 1U
#define RESEN (1U << 1)
#define INTEN 1U
#define WDT0 (1U << 18)
#define WDT_LOADVALUE 0xFF0000

#define GPIO_PORTF (1U << 5)
#define LED_RED (1U << 1)
#define LED_GREEN (1U << 3)

#define MILISECONDS_CONSTANT 1000
#define SECONDS_CONSTANT 1000000

void watchdog_init(void);
void gpio_init(void);
void WDT0_Handler(void);
void delay_miliseconds(unsigned int);
void delay_seconds(unsigned int);
void set_LED_RED(void);
void clear_LED_RED(void);
void set_LED_GREEN(void);
void clear_LED_GREEN(void);
void clear_LED(void);
void enable_watchdog0_interrupt(void);

#endif
