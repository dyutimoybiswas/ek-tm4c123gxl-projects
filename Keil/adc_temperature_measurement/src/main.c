#include "adc_temperature.h"

volatile long double output_temperature = 0;
volatile long double avg_output_temperature = 0;
volatile long counter = 0;

volatile int is_flag_used = 0;

void clear_LED_RED(){
	GPIOF->DATA &= ~LED_RED;
}

void led_init(){
	SYSCTL->RCGCGPIO |= GPIO_PORTF;
	GPIOF->DIR |= (LED_RED | LED_GREEN | LED_BLUE);
	GPIOF->DEN |= (LED_RED | LED_GREEN | LED_BLUE);
}

void adc_init(){
	
	SYSCTL->RCGCADC = R0;
	
	ADC0->ACTSS &= ~ASEN3;					//SS3 used
	//EMUX is kept 0 (default) for processor based sampling
	ADC0->SSMUX3 = 0x01;					//AIN1 selected
	ADC0->SSCTL3 |= (IE0 | END0);
	if(ADC0->PP & TS)
	{
		ADC0->SSCTL3 |= TS0;
	}
	ADC0->ACTSS |= ASEN3;
}

int main(){

	led_init();
	is_flag_used = 1;
	set_seconds(120);
	
	GPIOF->DATA |= LED_BLUE;

	if(SYSCTL->RCC & ~BYPASS)
	{
		adc_init();
	}

	while(1){
		ADC0->PSSI |= SS3;
		if(ADC0->RIS & INR3)
		{
			output_temperature += (MAX_TEMP - ((MULTIPLIER * VOLTAGE_RANGE * ADC0->SSFIFO3)/RESOLUTION));	//in degree celsius
			counter++;
			if(flag)
			{
				GPIOF->DATA &= ~LED_BLUE;
				avg_output_temperature = output_temperature / (long double)(counter);
				if(avg_output_temperature < LOWER_TEMPERATURE_LIMIT || avg_output_temperature > UPPER_TEMPERATURE_LIMIT)
				{	//beyond the safe range of operation
					GPIOF->DATA &= ~LED_GREEN;
					GPIOF->DATA |= LED_RED;
				}
				else
				{
					GPIOF->DATA &= ~LED_RED;
					GPIOF->DATA |= LED_GREEN;
				}
				output_temperature = 0;
				counter = 0;
				flag = 0;
				set_seconds(120);				//checks average temperature every 2 minutes 
			}
			ADC0->ISC |= IN3;
		}
	}
}
