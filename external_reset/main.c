#include "reset.h"

void Reset_Handler(){
	init();
	GPIOA->DATA = PA6;
	delay_s(1);					//pin 6 of GPIOA held high for 1 sec
	GPIOA->DATA = 0;
}

void delay_s(unsigned int n){
	for(unsigned volatile int i = 0; i < 1000000 * n; i++); 
}

void init(){
	SYSCTL->RCGCGPIO = 1U;
	GPIOA->DIR = PA6;
	GPIOA->DEN = PA6;
}

int main(){
	while(1){
		//TODO
	}
}
