#include "TM4C123GH6PM.h"
#include "constants.h"

void init(){
	/*PF2 (blue LED) as output*/
	SYSCTL->RCGCGPIO = PORTF;
	SYSCTL->RCC = (0x7 << 23);										//to divide system clock frequency. Refer Table 5-4 of datasheet, page 223
	GPIOF->DIR = LED_BLUE;
	GPIOF->DEN = LED_BLUE;
	
	/*configure system tick counter*/
	SysTick->LOAD = NO_OF_PULSES - 1U;
	SysTick->VAL = 0;
	SysTick->CTRL = (1U | (1U << 1) | (1U << 2));
}

void SysTick_Handler(){
	GPIOF->DATA ^= LED_BLUE;
}

int main(void){
	init();
	while(1){
		//TODO
	}
}
