#include <stdbool.h>
#include "rgb.h"


void HardFault_Handler(void)
{
	// HardFault_Handler provided to ensure program doesn't stop at HardFault
}

/* PF1, PF2 and PF3 to be used and corresponding PWM signals are M1PWM5, M1PWM6 and M1PWM7.
		So PWM1 module is clocked by setting RCGCPWM. */

#if defined(TURQUOISE)
void set_turquoise(void)
{
	SYSCTL->RCGCPWM = (1U << 1);
	SYSCTL->RCGC2 = (1U << 5);			
	GPIOF->AFSEL &= 0;
	PWM1->ENABLE &= 0;
	GPIOF->PCTL &= 0;
	GPIOF->AFSEL |= LED_RED;
	GPIOF->DIR = (LED_BLUE | LED_GREEN);
	GPIOF->PCTL |= 0x00000050;
	GPIOF->DEN = (LED_RED | LED_BLUE | LED_GREEN);
	GPIOF->DATA |= (LED_BLUE | LED_GREEN);
	SYSCTL->RCC = ((0x01 << 17) | (1U << 20));		// 16MHz/4 = 4MHz selected
	
	//M1PWM5
	PWM1->_2_CTL &= 0;								//to ensure CTL is cleared we use &=
	PWM1->_2_GENA = 0x08C;
	PWM1->_2_GENB |= 0x80C;
	PWM1->_2_LOAD = 400-1;   						// 4MHz/400 = 10 kHz selected i.e. time period = 100 microsec
	PWM1->_2_CMPA = 80-1;							// duty cycle (D) = 20% selected.
	PWM1->_2_CMPB |= 320-1;							// 1-D = 80%
	PWM1->_2_CTL = 1U;
	
	PWM1->ENABLE |= PWM5_EN;
}
#elif defined(MAGENTA)
void set_magenta(void)
{
	SYSCTL->RCGCPWM = (1U << 1);
	SYSCTL->RCGC2 = (1U << 5);			
	GPIOF->DEN = (LED_RED | LED_BLUE);
	GPIOF->AFSEL = (LED_RED | LED_BLUE);
	GPIOF->PCTL = 0x00000550;
	SYSCTL->RCC = ((0x01 << 17) | (1U << 20));		// 16MHz/4 = 4MHz selected
	
	//M1PWM5
	PWM1->_2_CTL &= 0;								//to ensure CTL is cleared we use &=
	PWM1->_2_GENA = 0x08C;
	PWM1->_2_GENB = 0x80C;
	PWM1->_2_LOAD = 400-1;   						// 4MHz/400 = 10 kHz selected i.e. time period = 100 microsec
	PWM1->_2_CMPA = 240-1;							// duty cycle (D) = 60% selected.
	PWM1->_2_CMPB = 160-1;							// 1-D = 40%
	PWM1->_2_CTL = 1U;
	
	//M1PWM6 & M1PWM7
	PWM1->_3_CTL &= 0;								//to ensure CTL is cleared we use &=
	PWM1->_3_GENA |= 0x08C;
	PWM1->_3_GENB |= 0x80C;
	PWM1->_3_LOAD |= 400-1;   						// 4MHz/400 = 10 kHz selected i.e. time period = 100 microsec
	PWM1->_3_CMPA |= 120-1;							// duty cycle (D) = 30% selected.
	PWM1->_3_CMPB |= 280-1;							// 1-D = 70%
	PWM1->_3_CTL |= 1U;
	
	PWM1->ENABLE = (PWM5_EN | PWM6_EN);				//PWM5, PWM6 enabled
}
#elif defined(ORANGE)
void set_orange(void)
{
	SYSCTL->RCGCPWM = (1U << 1);
	SYSCTL->RCGC2 = (1U << 5);			
	GPIOF->DEN = (LED_RED | LED_GREEN);
	GPIOF->AFSEL = LED_GREEN;
	GPIOF->PCTL = 0x00005000;
	GPIOF->DIR = LED_RED;
	GPIOF->DATA |= LED_RED;
	SYSCTL->RCC = ((0x01 << 17) | (1U << 20));		// 16MHz/4 = 4MHz selected
	
	//M1PWM7
	PWM1->_3_CTL &= 0;								//to ensure CTL is cleared we use &=
	PWM1->_3_GENA |= 0x08C;
	PWM1->_3_GENB |= 0x80C;
	PWM1->_3_LOAD |= 400-1;   						// 4MHz/400 = 10 kHz selected i.e. time period = 100 microsec
	PWM1->_3_CMPA |= 80-1;							// duty cycle (D) = 20% selected.
	PWM1->_3_CMPB |= 320-1;							// 1-D = 80%
	PWM1->_3_CTL |= 1U;
	
	PWM1->ENABLE = (PWM7_EN);						//PWM7 enabled
}
#endif

int main(void)
{
	#if defined(TURQUOISE)
	set_turquoise();
	#elif defined(MAGENTA)
	set_magenta();
	#elif defined(ORANGE)
	set_orange();
	#endif
	
	while(true)
	{
		// Do nothing.
	}
}
