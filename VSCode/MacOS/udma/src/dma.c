#include "dma.h"

// Control table must be 1024-byte aligned
uint8_t dmaControlTable[1024] __attribute__((aligned(1024)));

volatile bool rxDone = false;
volatile uint32_t dmaTransferCount = 0;
uint8_t txBuffer[BUFFER_SIZE];

void dma_setup()
{
    // enable uDMA controller
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA))
    {
        // wait till peripheral is ready
    }
    uDMAEnable();
    uDMAControlBaseSet(dmaControlTable);
    
    // Each supported peripheral has a designated channel
    // Configure UART0 TX channel (Channel 9)
    uDMAChannelAssign(UDMA_CH9_UART0TX);
    uDMAChannelAttributeDisable(UDMA_CH9_UART0TX,
                                UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                UDMA_ATTR_HIGH_PRIORITY | UDMA_ATTR_REQMASK);
    uDMAChannelControlSet(UDMA_CH9_UART0TX | UDMA_PRI_SELECT,
                          UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE |
                          UDMA_ARB_4);
}

void dma_start_tx_transfer(uint32_t size)
{
    uDMAChannelTransferSet(UDMA_CH9_UART0TX | UDMA_PRI_SELECT,
                           UDMA_MODE_BASIC,
                           txBuffer,
                           (void *)(UART0_BASE),  // UART data register
                           size);
    uDMAChannelEnable(UDMA_CH9_UART0TX);
}

int main(void)
{
    // set system clock frequency
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    uart_setup();
    dma_setup();
    
    // Enable global interrupts
    IntMasterEnable();

    while (true)
    {
        if (rxDone)
        {
            rxDone = false;
            
            // Only send if DMA TX is not busy
            if (dmaTransferCount > 0 && !uDMAChannelIsEnabled(UDMA_CH9_UART0TX))
            {
                dma_start_tx_transfer(dmaTransferCount);
            }
            
            // Reset for next batch
            dmaTransferCount = 0;
        }
    }
    
    return 0;
}
