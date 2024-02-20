#ifndef DELAY_H
#define DELAY_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

#if defined(SECOND)
#define LOAD_VALUE          15999999U
#elif defined(MILLISECOND)
#define LOAD_VALUE          15999U
#endif

void systick_setup(void);
void gpio_setup(void);
void systick_handler(void);

#endif
