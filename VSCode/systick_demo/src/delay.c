#include "delay.h"

void systick_handler(void)
{
    int32_t value = GPIOPinRead(GPIO_PORTF_AHB_BASE, GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTF_AHB_BASE, GPIO_PIN_3, ~value);          // toggle LED value
}

void systick_setup(void)
{
    SysTickPeriodSet(LOAD_VALUE);
    SysTickIntRegister(systick_handler);
    SysTickIntEnable();
    SysTickEnable();
}

void gpio_setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);                    // enable port F
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is enableds
    }
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);                       // enable HPB
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, GPIO_PIN_3);         // configure green LED pin as output
}

int main(int argc, char const *argv[])
{
    // Set system clock
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    gpio_setup();
    systick_setup();

    while (true)
    {
        // TODO
    }
    return 0;
}
