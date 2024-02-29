#ifndef SIGNAL_H
#define SIGNAL_H

#include "TM4C123GH6PM.h"
#include <stdbool.h>

#define GPIO_PORTF  1U << 5
#define LED_BLUE    1U << 2
#define T0          1U
#define TAEN        1U
#define TATOIM      1U
#define TATOMIS     1U
#define TATOCINT    1U

void signal_init(void);
void set_delay_time_us(unsigned int);
void gpio_init(void);
void TIMER0A_Handler(void);

static bool is_high                     = 1;
static unsigned volatile int delay_time = 300;				//default value = 300 us.

#endif
