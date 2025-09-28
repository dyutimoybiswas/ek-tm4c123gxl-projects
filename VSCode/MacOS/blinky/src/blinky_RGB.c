#include "blinky_RGB.h"

void setup(void)
{
    // Set system clock
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // enable port F
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is enabled
    }
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);       // enable HPB
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED);   // configure RGB pins as output

    // configure systick for delay
    SysTickPeriodSet(LOAD_VALUE);               
    SysTickIntRegister(systick_handler);        
    SysTickIntEnable();
    SysTickEnable();
}

void systick_handler(void)
{
    static uint32_t led = RED_LED;

    int32_t value = GPIOPinRead(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED);

    switch (value)
    {
    case 0:
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED, led);
        break;
    case RED_LED:
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED, 0);
        led = GREEN_LED;
        break;
    case GREEN_LED:
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED, 0);
        led = BLUE_LED;
        break;
    case BLUE_LED:
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, RED_LED | GREEN_LED | BLUE_LED, 0);
        led = RED_LED;
        break;
    default:
        break;
    }
}

int main(void)
{
    setup();    // setup pins, configure delay

    while (true)
    {
        // do nothing
    }
}
