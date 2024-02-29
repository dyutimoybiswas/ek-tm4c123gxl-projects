#include <stdbool.h>
#include "reset.h"

void Reset_Handler(void)
{
	init();
	GPIOA->DATA = PA6;
	delay_seconds(1);					//pin 6 of GPIOA held high for 1 sec
	GPIOA->DATA = 0;
}

void delay_seconds(unsigned int n)
{
	for(unsigned volatile int i = 0; i < 1000000 * n; i++); 
}

void init(void)
{
	SYSCTL->RCGCGPIO = R0;
	GPIOA->DIR = PA6;
	GPIOA->DEN = PA6;
}

int main(void)
{
	while(true)
	{
		// Do nothing.
	}
}
