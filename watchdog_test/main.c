#include "watchdog.h"

void set_LED_RED(){
	GPIOF->DATA |= LED_RED;
}

void clear_LED_RED(){
	GPIOF->DATA &= ~LED_RED;
}

void set_LED_GREEN(){
	GPIOF->DATA |= LED_GREEN;
}

void clear_LED_GREEN(){
	GPIOF->DATA &= ~LED_GREEN;
}

void clear_LED(){
	GPIOF->DATA &= ~(LED_GREEN | LED_RED);
}

void delay_miliseconds(unsigned int n){
	for(unsigned volatile int i = 0; i < MILISECONDS_CONSTANT * n; i++);
}

void delay_seconds(unsigned int n){
	for(unsigned volatile int i = 0; i < SECONDS_CONSTANT * n; i++);
}

void gpio_init(){
	SYSCTL->RCGCGPIO = GPIO_PORTF;
	GPIOF->DIR = LED_RED | LED_GREEN;
	GPIOF->DEN = LED_RED | LED_GREEN;
}

void watchdog_init(){
	SYSCTL->RCGCWD = W0;
	NVIC->ISER[0] = WDT0;
}

void enable_watchdog0_interrupt(){
	WATCHDOG0->CTL |= INTEN;
}

void WDT0_Handler(){
	clear_LED_GREEN();
	set_LED_RED();
	WATCHDOG0->ICR = 0;
}

int main(){
	//generating random delay
	unsigned int delay_time = (unsigned int)(rand() % MILISECONDS_CONSTANT);	//use SECONDS_CONSTANT for seconds delay
	watchdog_init();
	gpio_init();
	while(1){
		if(!(GPIOF->DATA & LED_RED)){
			set_LED_GREEN();
		}
		WATCHDOG0->LOAD = WDT_LOADVALUE;		//adjust the load value to trigger interrupt, keeping delay constant. If execution reaches here before delay, normal operation.
		enable_watchdog0_interrupt();				//triggers interrupt if value = 0 while delay is executed.
		delay_miliseconds(delay_time);			//adjust the delay to trigger interrupt, keeping load value constant. Argument can be random or a constant value.
	}
}
