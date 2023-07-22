#ifndef __RESET_H__
#define __RESET_H__

#include "TM4C123GH6PM.h"

#define PA6 (1U << 6)

void init(void);
void delay_s(unsigned int);
void Reset_Handler(void);

#endif
