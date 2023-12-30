#include "TM4C123GH6PM.h"
#include "uart_functions.h"
#include "setup.h"

void uart_clear(void)
{
	for(counter = 0; clear_screen[counter] != '\0'; counter++) uart_write(clear_screen[counter]);
	for(counter = 0; cursor_home[counter] != '\0'; counter++) uart_write(cursor_home[counter]);
}

void uart_write(char c)
{
	/* wait while transmit buffer is full. */
	while(UART1->FR & TXF);
	
	/* write to buffer and turn on green LED. */
	UART1->DR = c;
	GPIOF->DATA |= LED_GREEN;
}

char uart_read(void)
{
	/* wait while receive buffer is empty. */
	while(UART1->FR & RXE);
	
	/* return read character. */
	return (char)UART1->DR;
}
