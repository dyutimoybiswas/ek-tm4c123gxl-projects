#include <stdbool.h>
#include "pwm_constants.h"


void HardFault_Handler(void)
{
	// HardFault_Handler provided to ensure program doesn't stop at HardFault
}

void init(void)
{
	/* PF2 to be used and corresponding PWM signal is M1PWM6. so PWM1 module is clocked by setting RCGCPWM. */
	//PWM: afsel, pctl, rcc-pwmdiv, rcc-usepwmdiv, pwm1ctl, pwm1gena, pwm1genb, pwm1load, pwm1cmpa, pwm1cmpb, pwm1ctl, pwmenable
	SYSCTL->RCGCPWM = (1U << 1);
	SYSCTL->RCGC2 = PORTF;			
	GPIOF->DEN = LED_BLUE;
	GPIOF->AFSEL = LED_BLUE;
	GPIOF->PCTL = 0x00000500;
	SYSCTL->RCC = ((0x06 << 17) | (1U << 20));	// 16MHz/64 = 250kHz selected
	
	PWM1->_3_CTL &= 0;							//to ensure CTL is cleared we use &=
	PWM1->_3_GENA = 0x08C;
	PWM1->_3_GENB = 0x080C;
	PWM1->_3_LOAD = 50000-1;   					// 250kHz/50000 = 5 Hz selected i.e. time period = 200 msec
	PWM1->_3_CMPA = 12500-1;					// duty cycle (D) = 75% selected. Since count down, 25% is set here
	PWM1->_3_CMPB = 37500-1;					// 1-D = 25%. Since count down, 75% is set here 
	PWM1->_3_CTL = 1U;
	PWM1->ENABLE = (1U << 6);					//PWM6 enabled
}

int main(void)
{
	init();
	while(true)
	{
		// Do nothing.
	}
}
