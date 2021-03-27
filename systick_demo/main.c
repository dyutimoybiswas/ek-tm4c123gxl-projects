#include "demo.h"

void init(void){
	SYSCTL->RCGCGPIO = (1U << 5);
	SYSCTL->GPIOHBCTL = (1U << 5);
	GPIOF_AHB->DIR = LED_GREEN;
	GPIOF_AHB->DEN = LED_GREEN;
}

void SysTick_Handler(void){
	if(GPIOF_AHB->DATA & LED_GREEN){
		GPIOF_AHB->DATA = 0;
	}else{
		GPIOF_AHB->DATA = LED_GREEN;
	}
}

int main(void){
	init();
	SysTick->LOAD = CLK_FREQ - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 1U | (1U << 1) | (1U << 2);
	while(1);
}
