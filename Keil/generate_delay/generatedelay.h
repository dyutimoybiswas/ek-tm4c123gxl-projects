#ifndef __GENERATEDELAY_H__
#define __GENERATEDELAY_H__

#include "TM4C123GH6PM.h"

#define SECONDS_PRESCALE 245
#define SECONDS_CONSTANT 1.00352
#define MILISECONDS_CONSTANT 4.096

#define R0 1U
#define TAEN 1U
#define CFG_16_BIT 0x04
#define ONE_SHOT 0x01
#define TACDIR (1U << 4)
#define TATOIM 1U
#define TATOCINT 1U
#define TATOMIS 1U

void timer_init(void);
void set_seconds(unsigned int);
void set_miliseconds(unsigned int);
void use_indicator(void);				//green LED stays ON for specified time
void use_flag(void);							//sets flag variable at timeout
void clear_flag(void);
int get_flag(void);							//to get value of flag variable
void disable_indicator(void);
void set_LED_GREEN(void);
void clear_LED_GREEN(void);
void disable_timer(void);				//stops timer from counting
void clear_handler_counter(void);
void TIMER0A_Handler(void);
void HardFault_Handler(void);

extern unsigned volatile int seconds;
extern unsigned volatile int miliseconds;
extern unsigned volatile int handler_counter;
extern volatile int is_seconds;
extern volatile int is_miliseconds;
extern volatile int is_indicator_enabled;
extern volatile int is_flag_used;
extern volatile int flag;

#define GPIO_PORTF (1U << 5)
#define LED_GREEN (1U << 3)

#endif
