#include "spi_loopback.h"

void led_setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // enable port F
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is enabled
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, BLUE_LED);   // configure blue led pin as output
}

void systick_setup(void)
{
    SysTickPeriodSet(LOAD_VALUE);               
    SysTickIntRegister(systick_handler);        
    SysTickIntEnable();
    SysTickEnable();
}

void spi_setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);      // enable SSI1 peripheral
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI1))
    {
        // wait till peripheral is enabled
    }
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);     // enable port D
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
    {
        // wait till peripheral is enabled
    }
    GPIOPinConfigure(GPIO_PD0_SSI1CLK);     // configure pin D0 for SSI1 clock
    GPIOPinConfigure(GPIO_PD1_SSI1FSS);     // configure pin D1 for SSI1 frame signal
    GPIOPinConfigure(GPIO_PD2_SSI1RX);      // configure pin D2 for SSI1 receive
    GPIOPinConfigure(GPIO_PD3_SSI1TX);      // configure pin D3 for SSI1 transmit
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);   // configure pins D0, D1, D2, D3 for SSI1

    SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_1, SSI_MODE_MASTER, BIT_RATE, DATA_WIDTH);
    SSIEnable(SSI1_BASE);    // enable SSI1
}

void master_write(uint8_t data)
{
    uint32_t buffer_data;
    SSIDataPut(SSI1_BASE, data);
    SSIDataGet(SSI1_BASE, &buffer_data);       // read data from SSI1
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_LED, buffer_data);
}

void systick_handler(void)
{
    static bool write = true;
    if (write)
    {
        master_write(BLUE_LED);
    }
    else
    {
        master_write(0U);   // turn off LED
    }
    write = !write;   // toggle write operation
}

int main(void)
{
    // Setup
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    led_setup();
    spi_setup();
    systick_setup();

    while (true)
    {
        // do nothing   
    }
}
