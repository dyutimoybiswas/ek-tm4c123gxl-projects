#include "adc_temperature.h"


void set_seconds(unsigned int m)
{
	is_seconds = 1;
	handler_counter = 0;
	seconds = (unsigned int)((m * SECONDS_CONSTANT) + 1);
	timer_init();
}

void timer_init()
{
	SYSCTL->RCGCTIMER |= R0;
	TIMER0->CTL &= ~TAEN;
	TIMER0->CFG |= CFG_16_BIT;								// 16 bit mode
	TIMER0->TAMR |= (ONE_SHOT | TACDIR);					// ONE SHOT mode, count up
	if(is_seconds)
	{
		TIMER0->TAPR = SECONDS_PRESCALE - 1;
	}
	TIMER0->IMR |= TATOIM;
	NVIC_EnableIRQ(TIMER0A_IRQn);
	TIMER0->CTL |= TAEN;
}

void TIMER0A_Handler()
{
	handler_counter++;
	if(is_indicator_enabled)
	{
		GPIOF->DATA |= LED_GREEN;
	}
	TIMER0->ICR |= TATOCINT;
	if((is_seconds) && (3 * seconds <= handler_counter))
	{
		if(is_indicator_enabled)
		{
			GPIOF->DATA &= ~LED_GREEN;
		}
		if(is_flag_used) 
		{
			flag = 1;
		}
	}
	else
	{
		timer_init();
	}
}		

void use_indicator()
{
	is_indicator_enabled = 1;
	SYSCTL->RCGCGPIO |= GPIO_PORTF;
	GPIOF->DIR |= LED_GREEN;
	GPIOF->DEN |= LED_GREEN;
}

void disable_indicator()
{
	is_indicator_enabled = 0;
	SYSCTL->RCGCGPIO &= ~GPIO_PORTF;
	GPIOF->DIR &= ~LED_GREEN;
	GPIOF->DEN &= ~LED_GREEN;
}

void HardFault_Handler()
{
 	//added to prevent going into hardfault during execution
}
