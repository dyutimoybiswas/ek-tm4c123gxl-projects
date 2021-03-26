#ifndef __RESET_H__
#define __RESET_H__

#define PA6 (1U << 6)

void init(void);
void delay_s(unsigned int);
void Reset_Handler(void);

#endif
