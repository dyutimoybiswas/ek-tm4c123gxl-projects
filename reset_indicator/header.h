#ifndef __HEADER_H__
#define __HEADER_H__

#include "TM4C123GH6PM.h"

#define LED_GREEN (1U << 3)
#define GPIO_PORTF (1U << 5)

void init(void);
void Reset_Handler(void);
void blink_green_on_reset(void);
void delay(void);
void set_onboard_led_green(void);
void clear_onboard_led_green(void);

#endif
