#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "TM4C123GH6PM.h"

#define PORTF           1U << 5
#define LED_BLUE        1U << 2
#define CLK_FREQ        16000000U
#define NO_OF_PULSES    0x100000
#define ENABLE          1U
#define INTEN           1U << 1
#define CLKSRC          1U << 2

void init(void);
void SysTick_Handler(void);

#endif
