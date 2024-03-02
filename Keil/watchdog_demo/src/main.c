#include "watchdog.h"

#if defined(MILLISECONDS)
void delay(unsigned int n)
{
	for(unsigned volatile int i = 0; i < MILISECONDS_CONSTANT * n; i++);
}
#elif defined(SECONDS)
void delay(unsigned int n)
{
	for(unsigned volatile int i = 0; i < SECONDS_CONSTANT * n; i++);
}
#endif

void gpio_init(void)
{
	SYSCTL->RCGCGPIO = GPIO_PORTF;
	GPIOF->DIR = LED_RED | LED_GREEN;
	GPIOF->DEN = LED_RED | LED_GREEN;
}

void watchdog_init(void)
{
	SYSCTL->RCGCWD = W0;
	NVIC->ISER[0] = WDT0;
}

void enable_watchdog0_interrupt(void)
{
	WATCHDOG0->CTL |= INTEN;
}

void WDT0_Handler(void)
{
	GPIOF->DATA &= ~LED_GREEN;
	GPIOF->DATA |= LED_RED;
	WATCHDOG0->ICR = 0;
}

int main(void)
{
	//generating random delay
	unsigned int delay_time = (unsigned int)(rand() % CONSTANT);
	watchdog_init();
	gpio_init();

	while(true)
	{
		if(!(GPIOF->DATA & LED_RED))
		{
			GPIOF->DATA |= LED_GREEN;
		}
		WATCHDOG0->LOAD = WDT_LOADVALUE;		//adjust the load value to trigger interrupt, keeping delay constant. If execution reaches here before delay, normal operation.
		enable_watchdog0_interrupt();			//triggers interrupt if value = 0 while delay is executed.
		delay(delay_time);						//adjust the delay to trigger interrupt, keeping load value constant. Argument can be random or a constant value.
	}
}
