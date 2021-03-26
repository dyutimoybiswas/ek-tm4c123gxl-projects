#ifndef __SIGNAL_H__
#define __SIGNAL_H__

#define GPIO_PORTF (1U << 5)
#define LED_BLUE (1U << 2)

#define T0 1U
#define TAEN 1U
#define TATOIM 1U
#define TATOMIS 1U
#define TATOCINT 1U

void signal_init(void);
void set_delay_time_us(unsigned int);
void gpio_init(void);
void TIMER0A_Handler(void);
void set_LED_BLUE(void);
void clear_LED_BLUE(void);

extern unsigned volatile int is_high;
extern unsigned volatile int delay_time;

#endif
