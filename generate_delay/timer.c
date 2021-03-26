#include "TM4C123GH6PM.h"
#include "generatedelay.h"

unsigned volatile int seconds = 0;
unsigned volatile int miliseconds = 0;
unsigned volatile int handler_counter = 0;
volatile int is_seconds = 0;
volatile int is_miliseconds = 0;
volatile int is_indicator_enabled = 0;
volatile int is_flag_used = 0;
volatile int flag = 0;

void clear_handler_counter(){
	handler_counter = 0;
}

void use_flag(){
	is_flag_used = 1;
}

int get_flag(){
	return flag;
}

void clear_flag(){
	flag = 0;
}

void disable_timer(){
	TIMER0->CTL &= ~TAEN;
}

void set_seconds(unsigned int m){
	is_seconds = 1;
	clear_handler_counter();
	seconds = (unsigned int)((m * SECONDS_CONSTANT) + 1);
	timer_init();
}

void set_miliseconds(unsigned int m){
	is_miliseconds = 1;
	clear_handler_counter();
	miliseconds = (unsigned int)((m / MILISECONDS_CONSTANT));
	timer_init();
}		

void set_LED_GREEN(){
	GPIOF->DATA |= LED_GREEN;
}

void clear_LED_GREEN(){
	GPIOF->DATA &= ~LED_GREEN;
}

void timer_init(){
	SYSCTL->RCGCTIMER |= R0;
	disable_timer();
	TIMER0->CFG |= CFG_16_BIT;								//16 bit mode
	TIMER0->TAMR |= (ONE_SHOT | TACDIR);			//ONE SHOT mode, count up
	if(is_seconds) TIMER0->TAPR = SECONDS_PRESCALE - 1;
	else if(is_miliseconds) TIMER0->TAPR = 0;
	TIMER0->IMR |= TATOIM;
	NVIC_EnableIRQ(TIMER0A_IRQn);
	TIMER0->CTL |= TAEN;
}

void TIMER0A_Handler(){
	handler_counter++;
	if(is_indicator_enabled) set_LED_GREEN();
	TIMER0->ICR |= TATOCINT;
	if(((is_seconds) && (3 * seconds <= handler_counter)) || ((is_miliseconds) && (3 * miliseconds <= handler_counter))){
		if(is_indicator_enabled)clear_LED_GREEN();
		if(is_flag_used) flag = 1;
	}
	else timer_init();
}		

void use_indicator(){
	is_indicator_enabled = 1;
	SYSCTL->RCGCGPIO |= GPIO_PORTF;
	GPIOF->DIR |= LED_GREEN;
	GPIOF->DEN |= LED_GREEN;
}

void disable_indicator(){
	is_indicator_enabled = 0;
	SYSCTL->RCGCGPIO &= ~GPIO_PORTF;
	GPIOF->DIR &= ~LED_GREEN;
	GPIOF->DEN &= ~LED_GREEN;
}

void HardFault_Handler(){
	//added to prevent going into hardfault during execution
}
