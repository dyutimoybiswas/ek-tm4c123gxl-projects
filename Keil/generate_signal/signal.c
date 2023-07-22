#include "signal.h"

unsigned volatile int is_high = 1;
unsigned volatile int delay_time = 300;				//default value = 300 us.

void set_delay_time_us(unsigned int time){
	delay_time = time;
}

void signal_init(){
	gpio_init();
	SYSCTL->RCGCTIMER |= T0;
	TIMER0->CTL &= ~TAEN;
	TIMER0->CFG = 0;
	TIMER0->TAMR |= 0x02;			//periodic
	TIMER0->CFG = 0x04;				//16-bit
	TIMER0->TAILR = delay_time;		//set custom delay time
	//TIMER0->TAPR = 249U;		//to observe functionality
	TIMER0->IMR |= TATOIM;
	NVIC_EnableIRQ(TIMER0A_IRQn);
	TIMER0->CTL |= TAEN;
}

void set_LED_BLUE(){
	GPIOF->DATA |= LED_BLUE;
}

void clear_LED_BLUE(){
	GPIOF->DATA &= ~LED_BLUE;
}

void TIMER0A_Handler(){
	if(TIMER0->MIS & TATOMIS){
		if(is_high) set_LED_BLUE();
		else clear_LED_BLUE();
		is_high = !is_high;
		TIMER0->ICR |= TATOCINT;
	}
}

void gpio_init(){
	SYSCTL->RCGCGPIO |= GPIO_PORTF;
	GPIOF->DIR = LED_BLUE;
	GPIOF->DEN = LED_BLUE;
}
