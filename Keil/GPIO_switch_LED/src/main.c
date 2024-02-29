#include <stdbool.h>
#include "ports.h"

void init(void)
{
	SYSCTL->RCGCTIMER |= (1U << 2);			//Timer 2
	SYSCTL->RCGCGPIO = (1U | (1U << 1));	//Port A - digital input, Port B - digital output
	GPIOA->DIR = PA7;						//PA7 output
	GPIOB->DIR = 0;							//PB4 input
	GPIOA->DEN = PA7;						//PA7 digital pin
	GPIOB->DEN = PB4;						//PB4 digital pin
	GPIOB->IM = PB4;						//PB4 interrupt pin
	GPIOB->IS = PB4;						//level-triggered interrupt
	NVIC->ISER[0] |= (1U << 1);
}

void timer_init(void)
{
	TIMER2->CTL = 0;							//clear timer
	TIMER2->CFG = 0x04U;						//16-bit config
	TIMER2->TAMR = 0x02U;						//Periodic mode
	TIMER2->TBMR = 0x01U;						//One-shot mode
	TIMER2->TAILR = (SYS_CLK/PRESCALE_A) - 1U;
	TIMER2->TAPR = PRESCALE_A - 1U;
	TIMER2->TBILR = (SYS_CLK/PRESCALE_B) - 1U;
	TIMER2->TBPR = PRESCALE_B - 1U;
	TIMER2->IMR = (1U | (1U << 8));				//interrupts on timeout
	NVIC->ISER[0] |= ((1U << 23) | (1U << 24));	//trigger TIMER2A_Handler
	TIMER2->CTL |= 1U;							//enable timer
}

void TIMER2A_Handler(void)
{
	if(TIMER2->RIS & 1U)
	{
		if(status)
		{
			GPIOA->DATA ^= PA7;
		}
		else
		{
			GPIOA->DATA = 0;
		}
	}
	TIMER2->ICR = 1U;
}

void TIMER2B_Handler(void)
{
	if(TIMER2->RIS & (1U << 8))
	{
		status = !status;
	}
	TIMER2->ICR = (1U << 8);
}

void GPIOB_Handler(void)
{
	if(GPIOB->RIS & PB4)
	{
		// Do nothing
	}
	else if(GPIOB->DATA & PB4)
	{
		TIMER2->CTL |= (1U << 8);
	}
}

int main(void)
{
	init();
	timer_init();
	while(true)
	{
		// Do nothing
	}
}
