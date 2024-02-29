#include "signal.h"

void set_delay_time_us(unsigned int time)
{
	delay_time = time;
}

void signal_init(void)
{
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

void TIMER0A_Handler(void)
{
	if(TIMER0->MIS & TATOMIS)
	{
		if(is_high)
		{
			GPIOF->DATA |= LED_BLUE;
			is_high = false;
		}
		else
		{
			GPIOF->DATA &= ~LED_BLUE;
			is_high = true;
		}
		TIMER0->ICR |= TATOCINT;
	}
}

void gpio_init(void)
{
	SYSCTL->RCGCGPIO |= GPIO_PORTF;
	GPIOF->DIR = LED_BLUE;
	GPIOF->DEN = LED_BLUE;
}
