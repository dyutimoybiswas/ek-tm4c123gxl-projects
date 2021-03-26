#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define PORTF (1U << 5)
#define LED_BLUE (1U << 2)
#define CLK_FREQ 16000000U
#define NO_OF_PULSES 0x100000

void init(void);
void SysTick_Handler(void);

#endif
