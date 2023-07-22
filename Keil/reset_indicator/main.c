#include "header.h"

void init(void){
	SYSCTL->RCGCGPIO = GPIO_PORTF;
	SYSCTL->GPIOHBCTL = GPIO_PORTF;
	GPIOF_AHB->DIR = LED_GREEN;
	GPIOF_AHB->DEN = LED_GREEN;
}

void blink_green_on_reset(void){
	set_onboard_led_green();
	delay();
	clear_onboard_led_green();
}

void delay(void){
	for(volatile int i = 0; i < 1000000; i++);
}

void Reset_Handler(void){
	init();
	blink_green_on_reset();
}

void set_onboard_led_green(void){
	GPIOF_AHB->DATA = LED_GREEN;
}

void clear_onboard_led_green(void){
	GPIOF_AHB->DATA = 0;
}

int main(void){
	while(1);
}
