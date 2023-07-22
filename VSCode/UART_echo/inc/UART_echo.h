#ifndef UART_ECHO_H
#define UART_ECHO_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"

#define GREEN_LED GPIO_PIN_3
#define BAUD_RATE 115200

void setup();

#endif