#include "demo.h"

void init(void){
	SYSCTL->RCGCGPIO = (1U << 5);
	GPIOF->DIR = LED_BLUE;
	GPIOF->DEN = LED_BLUE;
}

void timerA_delay(void){
	//generate 1 sec delay
	SYSCTL->RCGCTIMER = (1U << 1);
	TIMER1->CTL = 0;
	TIMER1->CFG = 4U;
	TIMER1->TAMR = (1U << 1) | (1U << 4);					//set 4th bit for count up, clear for count down
	//TIMER1->TAILR = (CLK_FREQ/PRESCALE) - 1U;		//comment for count up
	TIMER1->TAILR = 0;
	TIMER1->TAPR = PRESCALE - 1U;
	TIMER1->ICR = 1U;
	TIMER1->CTL = 1U;
	TIMER1->IMR = 1U;					//timer to be used as interrupt
	NVIC->ISER[0] = (1U << 21);
}

void TIMER1A_Handler(void){
	if(TIMER1->MIS & 1U){
		GPIOF->DATA = ~GPIOF->DATA;
	}
	TIMER1->ICR = 1U;
}

int main(void){
	init();
	timerA_delay();
	while(1){
	}
}

