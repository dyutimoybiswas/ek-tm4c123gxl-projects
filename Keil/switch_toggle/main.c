#include "switch.h"

volatile int usr_sw1_flag;
volatile int usr_sw2_flag;

void init(void){
	SYSCTL->RCGCGPIO = GPIO_PORTF;
	SYSCTL->GPIOHBCTL = GPIO_PORTF;
	GPIOF_AHB->DIR = (LED_BLUE | LED_RED);
	GPIOF_AHB->LOCK = GPIO_UNLOCK;
	GPIOF_AHB->CR = (LED_BLUE | USR_SW1 | USR_SW2 | LED_RED);
	GPIOF_AHB->PUR = (USR_SW1 | USR_SW2);
	GPIOF_AHB->DEN = (LED_BLUE | USR_SW1 | USR_SW2 | LED_RED);
	usr_sw1_flag = 0;
	usr_sw2_flag = 0;
}

void debounce_delay(unsigned int ticks){
	for(unsigned volatile int i = 0; i < ticks; i++);
}

void blink_delay(unsigned int ticks){
	for(unsigned volatile int i = 0; i < ticks; i++);
}

void blink_red_led(volatile int flag){
	if(flag){
		GPIOF_AHB->DATA |= LED_RED;
		blink_delay(1000000U);
		GPIOF_AHB->DATA = (USR_SW1 | USR_SW2);
		blink_delay(1000000U);
	}
}
	
void blink_blue_led(volatile int flag){
	if(flag){
		GPIOF_AHB->DATA |= LED_BLUE;
		blink_delay(1000000U);
		GPIOF_AHB->DATA = (USR_SW1 | USR_SW2);
		blink_delay(1000000U);
	}
}

int main(void){
	init();
	while(1){
		debounce_delay(CLK_FREQ/1000000);
		volatile int is_sw1_pressed = USR_SW1 & ~GPIOF_AHB->DATA;
		volatile int is_sw2_pressed = USR_SW2 & ~GPIOF_AHB->DATA;
		if(is_sw1_pressed | is_sw2_pressed){
			if(is_sw1_pressed){
				usr_sw1_flag = !usr_sw1_flag;
			}
			if(is_sw2_pressed){
				usr_sw2_flag = !usr_sw2_flag;
			}
		}else{
			blink_blue_led(usr_sw1_flag);
			blink_red_led(usr_sw2_flag);
		}	
	}
}
