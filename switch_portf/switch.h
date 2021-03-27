#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "TM4C123GH6PM.h"

#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define GPIO_PORTF (1U << 5)
#define USR_SW1 (1U << 4)
#define USR_SW2 1U
#define GPIO_UNLOCK 0x4C4F434BU
#define CLK_FREQ 16000000U

void init(void);
void debounce_delay(void);

#endif
