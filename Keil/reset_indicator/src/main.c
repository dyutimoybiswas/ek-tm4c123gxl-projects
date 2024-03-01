#include <stdbool.h>
#include "header.h"

void init(void)
{
	SYSCTL->RCGCGPIO = GPIO_PORTF;
	SYSCTL->GPIOHBCTL = GPIO_PORTF;
	GPIOF_AHB->DIR = LED_GREEN;
	GPIOF_AHB->DEN = LED_GREEN;
}

void blink_green_on_reset(void)
{
	GPIOF_AHB->DATA = LED_GREEN;
	delay();
	GPIOF_AHB->DATA = 0;
}

void delay(void)
{
	for(volatile int i = 0; i < 1000000; i++);
}

void Reset_Handler(void)
{
	init();
	blink_green_on_reset();
}

int main(void)
{
	while(true);
}
