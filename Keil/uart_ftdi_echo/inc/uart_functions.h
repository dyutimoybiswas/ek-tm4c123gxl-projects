#ifndef _UART_FUNCTIONS_H_
#define _UART_FUNCTIONS_H_

#define TXF		1U << 5
#define RXE		1U << 4

static const char* clear_screen = "\x1b[2J";
static const char* cursor_home = "\x1b[H";
static unsigned short counter;

void uart_clear(void);
void uart_write(char);
char uart_read(void);

#endif
