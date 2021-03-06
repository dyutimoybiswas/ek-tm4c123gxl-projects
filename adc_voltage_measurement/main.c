#include "adcvoltage.h"

volatile double voltage_value = 0;
const double max_voltage = 3.3;
const int max_adc = 0xFFF;
const int adc_resolution = 4096;

void adc_init(){
	SYSCTL->RCGCADC = R0;
	SYSCTL->RCGCGPIO = GPIO_PORTE;
	GPIOE->AFSEL = PE2;
	GPIOE->DEN &= ~PE2;							//clear for analog operation
	GPIOE->AMSEL = PE2;
	
	ADC0->ACTSS &= ~ASEN3;					//SS3 used
	//EMUX is kept 0 (default) for processor based sampling
	ADC0->SSMUX3 = 0x01;						//AIN1 selected
	ADC0->SSCTL3 |= (IE0 | END0);
	ADC0->ACTSS |= ASEN3;
}

int main(){
	if(SYSCTL->RCC & ~BYPASS) adc_init();
	while(1){
		ADC0->PSSI |= SS3;		//enable sampling continuously
		if(ADC0->RIS & INR3){
			volatile double voltage_difference = ((double)(max_adc - ADC0->SSFIFO3) / adc_resolution ) * max_voltage;
			voltage_value = max_voltage - voltage_difference;			//capture measured voltage
			ADC0->ISC |= IN3;
		}
	}
}
