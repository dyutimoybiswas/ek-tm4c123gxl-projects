#ifndef BLINKY_RGB_H
#define BLINKY_RGB_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"

#define LOAD_VALUE          15999999U
#define RED_LED            GPIO_PIN_1
#define BLUE_LED           GPIO_PIN_2
#define GREEN_LED          GPIO_PIN_3

void setup(void);
void systick_handler(void);

#endif