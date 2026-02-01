#include "blinky_RGB.h"
#include "task.h"

// Semaphores for sequencing
static SemaphoreHandle_t xSemRed;
static SemaphoreHandle_t xSemGreen;
static SemaphoreHandle_t xSemBlue;

// Task configurations (must be static - tasks run after main exits)
static TaskConfig_t redConfig, greenConfig, blueConfig;

void rgb_setup()
{
    // Set system clock to 16 MHz (internal oscillator)
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Enable and configure GPIO Port F for RGB LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // Wait for peripheral to be ready
    }
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED);
    
    // Turn off all LEDs initially
    GPIOPinWrite(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED, 0);
}

// Generic LED task
static void vLedTask(void *pvParameters)
{
    TaskConfig_t *config = (TaskConfig_t *)pvParameters;
    
    while (true)
    {
        // Take (acquire) own semaphore
        xSemaphoreTake(*config->ownSem, portMAX_DELAY);
        
        // LED ON
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, config->ledPin, config->ledPin);
        vTaskDelay(pdMS_TO_TICKS(LED_ON_TIME_MS));
        
        // LED OFF
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, config->ledPin, 0);
        vTaskDelay(pdMS_TO_TICKS(LED_OFF_TIME_MS));
        
        // Signal next task in the chain
        xSemaphoreGive(*config->nextSem);
    }
}

int main(void)
{
    rgb_setup();    // Initialize RGB LED GPIOs
    
    // Create binary semaphores
    xSemRed = xSemaphoreCreateBinary();
    xSemGreen = xSemaphoreCreateBinary();
    xSemBlue = xSemaphoreCreateBinary();
    
    // Configure tasks
    redConfig   = (TaskConfig_t){RED_LED, &xSemRed, &xSemGreen};
    greenConfig = (TaskConfig_t){GREEN_LED, &xSemGreen, &xSemBlue};
    blueConfig  = (TaskConfig_t){BLUE_LED, &xSemBlue, &xSemRed};
    
    // Create tasks with equal priority
    xTaskCreate(vLedTask, "Red",   configMINIMAL_STACK_SIZE, &redConfig,   1, NULL);
    xTaskCreate(vLedTask, "Green", configMINIMAL_STACK_SIZE, &greenConfig, 1, NULL);
    xTaskCreate(vLedTask, "Blue",  configMINIMAL_STACK_SIZE, &blueConfig,  1, NULL);
    
    // Give the Red semaphore to start the chain
    xSemaphoreGive(xSemRed);
    
    // Start the scheduler - this should never return
    vTaskStartScheduler();
    
    while (true)
    {
    }
}

