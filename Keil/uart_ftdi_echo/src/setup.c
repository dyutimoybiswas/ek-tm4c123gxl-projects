#include "setup.h"

void io_setup(void)
{
	/* enable clock - PORTF */
	SYSCTL->RCGCGPIO |= 0x20;
	
	/* configure IO */
	GPIOF->DIR |= LED_GREEN;
	GPIOF->DEN |= LED_GREEN;
}

void uart_setup(void)
{
	/* enable clock - UART1 and PORTB */
	SYSCTL->RCGCUART |= 0x02;
	SYSCTL->RCGCGPIO |= 0x02;
	
	/* enable UART functionality */
	GPIOB->AFSEL |= PB0 | PB1;
	GPIOB->PCTL |= (1U << 0) | (1U << 4);
	GPIOB->DEN |= PB0 | PB1;
	
	/* disable UART */
	UART1->CTL &= ~(UARTEN | TXEN | RXEN);
	
	/* UART configuration @ 115200 bps, 1 byte FIFO, 8 bits, PIOSC clock */
	UART1->IBRD = 8;
	UART1->FBRD = 44;
	UART1->LCRH |= 0x03U << 5;
	UART1->CC = 0x05U;
	
	/* enable transmit and receive */
	UART1->CTL |= UARTEN | TXEN | RXEN;
}
