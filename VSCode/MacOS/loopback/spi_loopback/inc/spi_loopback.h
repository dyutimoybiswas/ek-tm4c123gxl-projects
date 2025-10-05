#ifndef SPI_LOOPBACK_H
#define SPI_LOOPBACK_H

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/ssi.h"
#include "driverlib/systick.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"

#define LOAD_VALUE         15999999U
#define BLUE_LED           GPIO_PIN_2
#define BIT_RATE           1000000U   // 1MHz
#define DATA_WIDTH         4U         // 4-bit data

void led_setup(void);
void spi_setup(void);
void systick_setup(void);
void systick_handler(void);
void master_write(uint8_t);

#endif // SPI_LOOPBACK_H
