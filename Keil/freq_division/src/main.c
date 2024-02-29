#include <stdbool.h>
#include "constants.h"

void init(void)
{
	/* PF2 (blue LED) as output. */
	SYSCTL->RCGCGPIO = PORTF;
	SYSCTL->RCC = (0x7 << 23);		//to divide system clock frequency. Refer Table 5-4 of datasheet, page 223
	GPIOF->DIR = LED_BLUE;
	GPIOF->DEN = LED_BLUE;
	
	/* configure system tick counter. */
	SysTick->LOAD = NO_OF_PULSES - 1U;
	SysTick->VAL = 0;
	SysTick->CTRL = ENABLE | INTEN | CLKSRC;
}

void SysTick_Handler(void)
{
	GPIOF->DATA ^= LED_BLUE;
}

int main(void)
{
	init();
	while(true)
	{
		// Do nothing.
	}
}
