#include "pattern.h"

void init(void){
	SYSCTL->RCGCGPIO = (1U << 5);
	SYSCTL->GPIOHBCTL = (1U << 5);
	GPIOF_AHB->DIR = (LED_RED | LED_BLUE | LED_GREEN);
	GPIOF_AHB->DEN = (LED_RED | LED_BLUE | LED_GREEN);
}

void delay(void){
	for(volatile int i = 0; i < 5000000; i++);
}

int main(void){
	init();
	while(1){
		switch(state){
			case OFF:
				delay();
				GPIOF_AHB->DATA = 0;
				state = R;
			case R:
				delay();
				GPIOF_AHB->DATA = LED_RED;
				state = RG;
			case RG:
				delay();
				GPIOF_AHB->DATA = (LED_RED | LED_GREEN);
				state = G;
			case G:
				delay();
				GPIOF_AHB->DATA = LED_GREEN;
				state = GB;
			case GB:
				delay();
				GPIOF_AHB->DATA = (LED_GREEN | LED_BLUE);
				state = B;
			case B:
				delay();
				GPIOF_AHB->DATA = LED_BLUE;
				state = RB;
			case RB:
				delay();
				GPIOF_AHB->DATA = (LED_RED | LED_BLUE);
				state = RGB;
			case RGB:
				delay();
				GPIOF_AHB->DATA = (LED_RED | LED_GREEN | LED_BLUE);
				state = OFF;
		}
	}
}
