#include "i2c_loopback.h"

volatile uint8_t write = MASTER_WRITE;  // start with master write operation

void led_setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);        // enable port F
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
        // wait till peripheral is enabled
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED | BLUE_LED | GREEN_LED);   // configure RGB pins as output
}

void i2c_setup(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);                // enable I2C2 peripheral
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C2))
    {
        // wait till peripheral is enabled
    }

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);               // enable GPIOE peripheral for I2C2 pins
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
    {
        // wait till peripheral is enabled
    }
    GPIOPinConfigure(GPIO_PE4_I2C2SCL);
    GPIOPinConfigure(GPIO_PE5_I2C2SDA);                        // configure PE5 for I2C2 SDA
    GPIOPinTypeI2CSCL(GPIO_PORTE_BASE, GPIO_PIN_4);            // configure PE4 as I2C2 SCL
    GPIOPinTypeI2C(GPIO_PORTE_BASE, GPIO_PIN_5);               // configure PE5 as I2C2 SDA

    I2CLoopbackEnable(I2C2_BASE);                              // enable loopback mode
    I2CMasterInitExpClk(I2C2_BASE, SysCtlClockGet(), true);    // initialize I2C2 master, 400kbps
    I2CSlaveEnable(I2C2_BASE);                                 // enable I2C2 slave
    I2CSlaveInit(I2C2_BASE, SLAVE_ADDRESS);                    // initialize slave with address
}

void systick_setup(void)
{
    SysTickPeriodSet(LOAD_VALUE);               
    SysTickIntRegister(systick_handler);        
    SysTickIntEnable();
    SysTickEnable();
}

void master_write(void)
{
    I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDRESS, false);      // set slave address, false for write
    I2CMasterDataPut(I2C2_BASE, MASTER_WRITE_DATA);              // put data to be sent in data register
    I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_SEND);     // initiate send

    while (!(I2CSlaveStatus(I2C2_BASE) & I2C_SLAVE_ACT_RREQ))
    {
        // wait till slave receives data
    }
    uint32_t data = I2CSlaveDataGet(I2C2_BASE);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | GREEN_LED | BLUE_LED, data);
}

void slave_write(void)
{
    I2CMasterSlaveAddrSet(I2C2_BASE, SLAVE_ADDRESS, true);           // set slave address, true for read
    I2CMasterControl(I2C2_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);      // initiate receive

    // NOTE: master must initiate read before slave can send data
    while (!(I2CSlaveStatus(I2C2_BASE) & I2C_SLAVE_ACT_TREQ))
    {
        // wait till master requests data
    }
    I2CSlaveDataPut(I2C2_BASE, SLAVE_WRITE_DATA);                    // put data to be sent in data register
    uint32_t data = I2CMasterDataGet(I2C2_BASE);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | GREEN_LED | BLUE_LED, data);
}

void systick_handler(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_LED | GREEN_LED | BLUE_LED, 0); // turn off all LEDs
    if (write == MASTER_WRITE)
    {
        master_write();
        write = SLAVE_WRITE;
    }
    else
    {
        slave_write();
        write = MASTER_WRITE;
    }
}

int main(void)
{
    // Setup
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    led_setup();
    i2c_setup();
    systick_setup();

    while (true)
    {
        // do nothing   
    }

    return 0;
}
