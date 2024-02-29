#ifndef ADC_TEMPERATURE_H
#define ADC_TEMPERATURE_H

#include "TM4C123GH6PM.h"

#define SECONDS_PRESCALE        245
#define SECONDS_CONSTANT        1.00352
#define R0                      1U
#define TAEN                    1U
#define CFG_16_BIT              0x04
#define ONE_SHOT                0x01
#define TACDIR                  1U << 4
#define TATOIM                  1U
#define TATOCINT                1U
#define TATOMIS                 1U
#define GPIO_PORTF              1U << 5
#define LED_GREEN               1U << 3
#define BYPASS                  1U << 11
#define R0                      1U
#define TS0                     1U << 3
#define TS                      1U << 23
#define ASEN3                   1U << 3
#define END0                    1U << 1
#define IE0                     1U << 2
#define INR3                    1U << 3
#define IN3                     1U << 3
#define SS3                     1U << 3
#define GPIO_PORTF              1U << 5
#define LED_RED                 1U << 1
#define LED_BLUE                1U << 2
#define LED_GREEN               1U << 3

#define MAX_TEMP                147.5
#define MULTIPLIER              75
#define RESOLUTION              4096
#define VOLTAGE_RANGE           3.29
#define LOWER_TEMPERATURE_LIMIT -65		//-65 degrees Celsius
#define UPPER_TEMPERATURE_LIMIT 150		//150 degrees Celsius

void timer_init(void);
void set_seconds(unsigned int);
// void set_miliseconds(unsigned int);
void use_indicator(void);				//green LED stays ON for specified time
// void use_flag(void);					//sets flag variable at timeout
// void clear_flag(void);
// int get_flag(void);					    //to get value of flag variable
void disable_indicator(void);
// void set_LED_GREEN(void);
// void clear_LED_GREEN(void);
// void disable_timer(void);				//stops timer from counting
void clear_handler_counter(void);
void TIMER0A_Handler(void);
// void HardFault_Handler(void);
void adc_init(void);
void led_init(void);
// void set_LED_RED(void);
// void clear_LED_RED(void);
// void set_LED_BLUE(void);
// void clear_LED_BLUE(void);
// void set_LED_GREEN(void);
// void clear_LED_GREEN(void);
// void use_flag(void);
// int get_flag(void);
// void clear_flag(void);

extern unsigned volatile int seconds;
extern unsigned volatile int handler_counter;
extern volatile int is_seconds;
extern volatile int is_indicator_enabled;
extern volatile int is_flag_used;
extern volatile int flag;

extern volatile long double output_temperature;
extern volatile long double avg_output_temperature;
extern volatile long counter;

#endif
