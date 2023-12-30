#include <stdbool.h>
#include "setup.h"
#include "delay.h"
#include "uart_functions.h"

/**
*	Configure UART1 (PB0 & PB1)
* Listen for input from console
* Transmit received character back to console via UART1
* Turn on green LED during this operation
**/

int main(void)
{
	/* do setup. */
	io_setup();
	uart_setup();
	
	/* clear screen and set cursor to beginning of console beforehand. */
	uart_clear();
	
	while(true)
	{
		/* turn off green LED when not using UART. */
		GPIOF->DATA &= ~LED_GREEN;
		
		/* echo character. */
		received_character = uart_read();
		uart_write(received_character);
	}
}
