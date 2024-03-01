#ifndef PWM_CONSTANTS_H
#define PWM_CONSTANTS_H

#include "TM4C123GH6PM.h"

#define LED_RED     1U << 1
#define LED_BLUE    1U << 2
#define LED_GREEN   1U << 3
#define PORTF       1U << 5

void init(void);
void HardFault_Handler(void);

#endif
