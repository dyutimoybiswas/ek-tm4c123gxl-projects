#ifndef __PWM_CONSTANTS_H__
#define __PWM_CONSTANTS_H__
#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)
#define PWM5_EN (1U << 5)
#define PWM6_EN (1U << 6)
#define PWM7_EN (1U << 7)

extern unsigned volatile int duty_cycle_r;
#endif
