#ifndef __PORTS_H__
#define __PORTS_H__

#define PA7 (1U << 7)
#define PB4 (1U << 4)
#define SYS_CLK 16000000U
#define CONST_16BIT 65536U
#define PRESCALE_A 123U
#define PRESCALE_B 30U
#define TIMERB_TIMEOUT (1U << 8)

void init(void);
void timer_init(void);
void GPIOB_Handler(void);
void debounce_delay(unsigned int);
void TIMER2A_Handler(void);
void TIMER2B_Handler(void);

extern unsigned volatile int status;

#endif
