#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"

#define BAUD_RATE       115200
#define BUFFER_SIZE     64

extern volatile bool rxDone;
extern volatile uint32_t dmaTransferCount;
extern uint8_t txBuffer[BUFFER_SIZE];

void uart_handler();
void uart_setup();

void dma_setup();
void dma_start_tx_transfer(uint32_t size);

#endif