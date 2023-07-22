#ifndef __DEMO_H__
#define __DEMO_H__

#include "TM4C123GH6PM.h"

#define LED_GREEN (1U << 3)
#define CLK_FREQ 16000000U

void init(void);
void SysTick_Handler(void);

#endif
