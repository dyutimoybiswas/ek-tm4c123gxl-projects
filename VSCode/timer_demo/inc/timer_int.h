#ifndef TIMER_INT_H
#define TIMER_INT_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

#define PRESCALE            255
#define BLUE_LED            GPIO_PIN_2

void setup(void);

static volatile uint8_t value = 0;

#endif