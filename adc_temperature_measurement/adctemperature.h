#ifndef __ADCTEMPERATURE_H__
#define __ADCTEMPERATURE_H__

#include "../generate_delay/generatedelay.h"
#include "TM4C123GH6PM.h"

#define BYPASS (1U << 11)

#define R0 1U
#define TS0 (1U << 3)
#define TS (1U << 23)
#define ASEN3 (1U << 3)
#define END0 (1U << 1)
#define IE0 (1U << 2)
#define INR3 (1U << 3)
#define IN3 (1U << 3)
#define SS3 (1U << 3)

#define GPIO_PORTF (1U << 5)
#define LED_RED (1U << 1)
#define LED_BLUE (1U << 2)
#define LED_GREEN (1U << 3)

#define MAX_TEMP 147.5
#define MULTIPLIER 75
#define RESOLUTION 4096
#define VOLTAGE_RANGE 3.29
#define LOWER_TEMPERATURE_LIMIT -65		//-65�C
#define UPPER_TEMPERATURE_LIMIT 150		//150�C

void adc_init(void);
void led_init(void);
void set_LED_RED(void);
void clear_LED_RED(void);
void set_LED_BLUE(void);
void clear_LED_BLUE(void);
void set_LED_GREEN(void);
void clear_LED_GREEN(void);
void use_flag(void);
int get_flag(void);
void clear_flag(void);

extern volatile long double output_temperature;
extern volatile long double avg_output_temperature;
extern volatile long counter;

#endif
