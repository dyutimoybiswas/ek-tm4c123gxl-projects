#include "timer_int.h"

void timer_handler(void)    // for static compilation add this to interrupt vector table in startup
{
    //toggle blue LED
    value ^= BLUE_LED;
    GPIOPinWrite(GPIO_PORTF_AHB_BASE, BLUE_LED, value);
    TimerIntClear(TIMER3_BASE, TIMER_TIMB_TIMEOUT);
}

void setup(void)
{
    // set system clock frequency
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // enable gpio port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is ready
    }
    SysCtlGPIOAHBEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, BLUE_LED);

    // enable timer3B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3))
    {
        // wait till peripheral is ready
    }
    
    // register interrupts
    IntEnable(INT_TIMER3B_TM4C123);

    // timer
    TimerDisable(TIMER3_BASE, TIMER_B);
    TimerConfigure(TIMER3_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PERIODIC));
    TimerLoadSet(TIMER3_BASE, TIMER_B, SysCtlClockGet());
    TimerPrescaleSet(TIMER3_BASE, TIMER_B, PRESCALE);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMB_TIMEOUT);
    TimerEnable(TIMER3_BASE, TIMER_B);
}

int main(void)
{
    setup();
    
    while (true)
    {
        //uncomment below if not registering interrupt handler
        /*if (TimerIntStatus(TIMER3_BASE, false) & TIMER_TIMB_TIMEOUT)
        {
            value ^= BLUE_LED;
            // value = BLUE_LED;
            GPIOPinWrite(GPIO_PORTF_AHB_BASE, BLUE_LED, value);   
            TimerIntClear(TIMER3_BASE, TIMER_TIMB_TIMEOUT);         
        }*/
    }
    
    return 0;
}
