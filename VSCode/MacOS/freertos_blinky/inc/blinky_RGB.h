#ifndef BLINKY_RGB_H
#define BLINKY_RGB_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "FreeRTOS.h"
#include "semphr.h"

#define RED_LED            GPIO_PIN_1
#define BLUE_LED           GPIO_PIN_2
#define GREEN_LED          GPIO_PIN_3

// Delay times in milliseconds
#define LED_ON_TIME_MS      300
#define LED_OFF_TIME_MS     300

typedef struct 
{
    uint8_t ledPin;                 // LED GPIO pin
    SemaphoreHandle_t *ownSem;      // Semaphore to wait on
    SemaphoreHandle_t *nextSem;     // Semaphore to signal next task
} TaskConfig_t;

void rgb_setup(void);

#endif  // BLINKY_RGB_H