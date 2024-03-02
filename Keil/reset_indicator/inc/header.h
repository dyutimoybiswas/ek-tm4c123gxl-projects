#ifndef HEADER_H
#define HEADER_H

#include "TM4C123GH6PM.h"

#define LED_GREEN   1U << 3
#define GPIO_PORTF  1U << 5

void init(void);
void Reset_Handler(void);
void blink_green_on_reset(void);
void delay(void);

#endif
