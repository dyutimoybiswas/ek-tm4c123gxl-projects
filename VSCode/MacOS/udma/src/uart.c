#include "dma.h"

void uart_handler()
{
    UARTIntClear(UART0_BASE, UART_INT_RT);
    
    // Read all available bytes from FIFO
    while (UARTCharsAvail(UART0_BASE))
    {
        if (dmaTransferCount < BUFFER_SIZE)
        {
            txBuffer[dmaTransferCount++] = UARTCharGetNonBlocking(UART0_BASE);
        }
        else
        {
            UARTCharGetNonBlocking(UART0_BASE);  // Discard if full
        }
    }
    
    rxDone = true;
}

void uart_setup()
{
    // enable gpio port A
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
        // wait till peripheral is ready
    }
    
    // Configure pins
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // enable UART0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
    {
        // wait till peripheral is ready
    }
    
    // Configure UART
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), BAUD_RATE, 
                        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    
    // Enable FIFO (required for receive timeout)
    UARTFIFOEnable(UART0_BASE);
    
    // Enable DMA for TX only
    UARTDMAEnable(UART0_BASE, UART_DMA_TX);
    
    // Enable timeout interrupt (FIFO not empty)
    UARTIntRegister(UART0_BASE, uart_handler);
    UARTIntEnable(UART0_BASE, UART_INT_RT);
    
    UARTEnable(UART0_BASE);
}
