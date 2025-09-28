#ifndef COLOR_GENERATOR_H
#define COLOR_GENERATOR_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"

#define FREQ            25000                      // PWM generator block frequency - 25 kHz
#define RED_LED         GPIO_PIN_1
#define BLUE_LED        GPIO_PIN_2
#define GREEN_LED       GPIO_PIN_3

void setup(void);
void generate_color(uint8_t, uint8_t, uint8_t);

#endif