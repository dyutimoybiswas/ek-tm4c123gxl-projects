#include "switch.h"

void init(void){
	SYSCTL->RCGCGPIO = GPIO_PORTF;
	SYSCTL->GPIOHBCTL = GPIO_PORTF;
	GPIOF_AHB->DIR = (LED_BLUE | LED_RED);
	GPIOF_AHB->LOCK = GPIO_UNLOCK;
	GPIOF_AHB->CR = (LED_BLUE | USR_SW1 | USR_SW2 | LED_RED);
	GPIOF_AHB->PUR = (USR_SW1 | USR_SW2);
	GPIOF_AHB->DEN = (LED_BLUE | USR_SW1 | USR_SW2 | LED_RED);
}

void debounce_delay(void){
	for(unsigned volatile int i = 0; i < (CLK_FREQ/1000000); i++);
}

int main(void){
	init();
	while(1){
		debounce_delay();
		if(USR_SW1 & ~GPIOF_AHB->DATA){
			GPIOF_AHB->DATA = LED_BLUE;
		}else if(USR_SW2 & ~GPIOF_AHB->DATA){
			GPIOF_AHB->DATA = LED_RED;
		}else{
			GPIOF_AHB->DATA = 0;
		}
	}
}
