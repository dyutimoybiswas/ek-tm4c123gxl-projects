#include "UART_echo.h"

void uart_handler()    
{
    UARTIntClear(UART0_BASE, UART_INT_RT);

    while (UARTCharsAvail(UART0_BASE))
    {
        int32_t ch = UARTCharGet(UART0_BASE);
        UARTCharPut(UART0_BASE, ch);
        while (UARTBusy(UART0_BASE))
        {
            // wait till transmit FIFO is empty
        }
        GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);    // turn on LED when FIFO is non-empty
    }
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, 0);    // turn off LED when FIFO is empty
}

void setup()
{
    // set system clock frequency
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // register interrupts
    IntEnable(INT_UART0_TM4C123);

    // enable gpio port A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
        // wait till peripheral is ready
    }
    GPIOPinConfigure(GPIO_PA0_U0RX | GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // enable gpio port F
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is ready
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GREEN_LED);

    // enable UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
        // wait till peripheral is ready
    }
    UARTIntEnable(UART0_BASE, UART_INT_RT);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), BAUD_RATE, UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);
}

int main(void)
{
    setup();

    while (true)
    {
        // Listen for input
    }
    
    return 0;
}
