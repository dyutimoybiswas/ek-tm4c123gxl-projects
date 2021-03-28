#include "pwm_constants.h"

unsigned volatile int duty_cycle_r = 0;

//HardFault_Handler provided to ensure program doesn't stop at HardFault
void HardFault_Handler(){
	
}

void delay_msec(unsigned int n){
	for(unsigned volatile int i = 0; i < 1000 * n; i++);
}

void red_init(){
	SYSCTL->RCGCPWM = (1U << 1);
	SYSCTL->RCGC2 = (1U << 5);			
	GPIOF->AFSEL &= 0;
	PWM1->ENABLE &= 0;
	GPIOF->PCTL &= 0;
	GPIOF->AFSEL |= (LED_RED);
	GPIOF->PCTL |= 0x00000050;
	GPIOF->DEN = (LED_RED);
	SYSCTL->RCC = ((0x01 << 17) | (1U << 20));		// 16MHz/4 = 4MHz selected
	
	//M1PWM5
	PWM1->_2_CTL &= 0;														//to ensure CTL is cleared we use &=
	PWM1->_2_GENA = 0x08C;
	PWM1->_2_GENB |= 0x80C;
	PWM1->_2_LOAD = 400-1;   										// 4MHz/400 = 10 kHz selected i.e. time period = 100 microsec
	PWM1->_2_CTL = 1U;
	
	PWM1->ENABLE = PWM5_EN;
}

void set_cmp(){
		PWM1->_2_CMPA = duty_cycle_r - 1;
		PWM1->_2_CMPB = 400 - duty_cycle_r - 1;
		delay_msec(50);
}

int main(){
	red_init();
	while(1){
		//TODO
		if(duty_cycle_r == 400)duty_cycle_r = 0;
		duty_cycle_r += 10;
		set_cmp();
	}
}
