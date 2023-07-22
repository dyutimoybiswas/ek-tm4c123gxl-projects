#ifndef __ADCVOLTAGE_H__
#define __ADCVOLTAGE_H__

#include "TM4C123GH6PM.h"

#define BYPASS (1U << 11)

#define GPIO_PORTE (1U << 4)
#define PE2 (1U << 2)

#define R0 1U
#define ASEN3 (1U << 3)
#define END0 (1U << 1)
#define IE0 (1U << 2)
#define MASK3 (1U << 3)
#define INR3 (1U << 3)
#define IN3 (1U << 3)
#define SS3 (1U << 3)

void adc_init(void);

extern const double max_voltage;
extern const int max_adc;
extern const int adc_resolution;
extern volatile double voltage_value;

//commented to prevent execution going to hardfault
/*#define MAX_VOLTAGE 3.3
#define MAX_ADC 0x0FFF
#define ADC_RESOLUTION 4096*/

#endif
