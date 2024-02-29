#include "generate_delay.h"

void disable_timer(void)
{
	TIMER0->CTL &= ~TAEN;
}

#if defined(SECONDS)
void set_seconds(unsigned int m)
{
	clear_handler_counter();
	seconds = (unsigned int)((m * SECONDS_CONSTANT) + 1);
	timer_init();
}
#endif
#elif defined(MILLISECONDS)
void set_milliseconds(unsigned int m)
{
	handler_counter = 0;
	milliseconds = (unsigned int)((m / MILLISECONDS_CONSTANT));
	timer_init();
}
#endif

void timer_init(){
	SYSCTL->RCGCTIMER |= R0;
	disable_timer();
	TIMER0->CFG |= CFG_16_BIT;						//16 bit mode
	TIMER0->TAMR |= (ONE_SHOT | TACDIR);			//ONE SHOT mode, count up
	#if defined(SECONDS)
	TIMER0->TAPR = SECONDS_PRESCALE - 1;
	#endif
	#elif defined(MILLISECONDS)
	TIMER0->TAPR = 0;
	#endif
	TIMER0->IMR |= TATOIM;
	NVIC_EnableIRQ(TIMER0A_IRQn);
	TIMER0->CTL |= TAEN;
}

void TIMER0A_Handler(void)
{
	handler_counter++;
	if(is_indicator_enabled)
	{
		GPIOF->DATA |= LED_GREEN;
	}
	TIMER0->ICR |= TATOCINT;
	#if defined(SECONDS)
	if (3 * seconds <= handler_counter)
	{
		if(is_indicator_enabled)
		{
			GPIOF->DATA &= ~LED_GREEN;
		}
	}
	#endif
	#elif defined(MILLISECONDS)
	if (3 * miliseconds <= handler_counter)
	{
		if(is_indicator_enabled)
		{
			GPIOF->DATA &= ~LED_GREEN;
		}
	}
	#endif
}		

void use_indicator(void)
{
	is_indicator_enabled = true;
	SYSCTL->RCGCGPIO |= GPIO_PORTF;
	GPIOF->DIR |= LED_GREEN;
	GPIOF->DEN |= LED_GREEN;
}

void disable_indicator(void)
{
	is_indicator_enabled = false;
	SYSCTL->RCGCGPIO &= ~GPIO_PORTF;
	GPIOF->DIR &= ~LED_GREEN;
	GPIOF->DEN &= ~LED_GREEN;
}

void HardFault_Handler(void)
{
	//added to prevent going into hardfault during execution
}
