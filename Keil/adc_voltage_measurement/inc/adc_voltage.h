#ifndef ADC_VOLTAGE_H
#define ADC_VOLTAGE_H

#include "TM4C123GH6PM.h"

#define BYPASS          1U << 11
#define GPIO_PORTE      1U << 4
#define PE2             1U << 2
#define R0              1U
#define ASEN3           1U << 3
#define END0            1U << 1
#define IE0             1U << 2
#define MASK3           1U << 3
#define INR3            1U << 3
#define IN3             1U << 3
#define SS3             1U << 3
#define MAX_VOLTAGE     3.3
#define MAX_ADC         0xFFF
#define ADC_RESOLUTION  4096

void adc_init(void);

static volatile double voltage_value      = 0.0;
static volatile double voltage_difference = 0.0;

//commented to prevent execution going to hardfault
/*
#define MAX_VOLTAGE 3.3
#define MAX_ADC 0x0FFF
#define ADC_RESOLUTION 4096
*/

#endif
