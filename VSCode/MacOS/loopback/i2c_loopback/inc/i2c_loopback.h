#ifndef I2C_LOOPBACK_H
#define I2C_LOOPBACK_H

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"

#define SLAVE_ADDRESS      0x22
#define LOAD_VALUE         15999999U
#define RED_LED            GPIO_PIN_1
#define BLUE_LED           GPIO_PIN_2
#define GREEN_LED          GPIO_PIN_3
#define MASTER_WRITE_DATA  RED_LED | GREEN_LED      // yellow
#define SLAVE_WRITE_DATA   RED_LED | BLUE_LED       // magenta

void led_setup(void);
void i2c_setup(void);
void systick_setup(void);
void master_write(void);
void slave_write(void);
void systick_handler(void);

// write operation to perform
enum State
{
    MASTER_WRITE = 1,
    SLAVE_WRITE
};

#endif // I2C_LOOPBACK_H
