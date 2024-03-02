#ifndef PATTERN_H
#define PATTERN_H

#include "TM4C123GH6PM.h"

#define LED_RED 	1U << 1
#define LED_BLUE 	1U << 2
#define LED_GREEN 	1U << 3
#define CLK_FREQ 	16000000U
#define PRESCALE 	245

static enum {OFF, R, RG, G, GB, B, RB, RGB} state = R;

void init(void);
void delay(void);

#endif
