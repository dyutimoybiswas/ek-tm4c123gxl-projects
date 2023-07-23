#ifndef COLOR_GENERATOR_H
#define COLOR_GENERATOR_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"

#define FREQ 25000                      // PWM generator block frequency - 25 kHz
#define RED_LED GPIO_PIN_1
#define BLUE_LED GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
#define GREEN_WIFI_STARTED 102 / 255
#define BLUE_HTTP_STARTED 51 / 255
#define BLUE_WIFI_CONNECTED 153 / 255

void setup();
void init_wifi_started();
void init_http_started();
void init_wifi_connected();

#endif