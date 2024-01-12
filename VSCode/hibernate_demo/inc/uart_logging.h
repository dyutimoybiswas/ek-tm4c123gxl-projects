#ifndef UART_LOGGING_H
#define UART_LOGGING_H

#define BAUD_RATE   115200
#define NULL_CHAR   '\0'

void uart_setup(void);
void uart_init(void);
void uart_write(const char*);

static const char* newline_carriage_return = "\n\r";

#endif