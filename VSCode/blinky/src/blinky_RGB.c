#include "blinky_RGB.h"

void setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // enable port F
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is enabled
    }
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);       // enable HPB
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);   // configure RGB pins as output
}

void delay(void)
{
    for (uint32_t i = 0; i < 200000; i++)
    {
        // Do nothing.
    }
}

int main(void)
{
    setup();    // setup pins

    while (true)
    {
        // blink Red LED
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1, GPIO_PIN_1);
        delay();
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_1, 0);
        delay();

        // blink Blue LED
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_2, GPIO_PIN_2);
        delay();
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_2, 0);
        delay();

        // blink Green LED
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_3, GPIO_PIN_3);
        delay();
        GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_3, 0);
        delay();
    }
    
    return 0;
}
