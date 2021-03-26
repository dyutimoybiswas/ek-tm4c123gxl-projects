#ifndef __DEMO_H__
#define __DEMO_H__

#include "TM4C123.h"
#include "TM4C123GH6PM.h"

#define LED_BLUE (1U << 2)
#define CLK_FREQ 16000000U
#define PRESCALE 250U

void init(void);
void timerA_delay(void);
void TIMER1A_Handler(void);

#endif
