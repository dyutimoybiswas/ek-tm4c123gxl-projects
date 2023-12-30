#ifndef _SETUP_H_
#define _SETUP_H_

#include "TM4C123GH6PM.h"

#define LED_GREEN		1U << 3
#define PB0					1U << 0
#define PB1					1U << 1
#define UARTEN			1U << 0
#define TXEN				1U << 8
#define RXEN				1U << 9

static char received_character;

void io_setup(void);
void uart_setup(void);

#endif
