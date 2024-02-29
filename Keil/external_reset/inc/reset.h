#ifndef RESET_H
#define RESET_H

#include "TM4C123GH6PM.h"

#define R0          1U
#define PA6         1U << 6

void init(void);
void delay_seconds(unsigned int);
void Reset_Handler(void);

#endif
