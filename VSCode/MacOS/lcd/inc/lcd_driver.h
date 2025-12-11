#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"

#define LCD_RS_PIN              GPIO_PIN_0
#define LCD_E_PIN               GPIO_PIN_1
#define LCD_D4_PIN              GPIO_PIN_2
#define LCD_D5_PIN              GPIO_PIN_3
#define LCD_D6_PIN              GPIO_PIN_4
#define LCD_D7_PIN              GPIO_PIN_5
#define LCD_CLEAR               0x01        // Clear display
#define LCD_HOME                0x02        // Return home
#define LCD_ENTRY_MODE          0x06        // Entry mode set (increment cursor, no shift)
#define LCD_DISPLAY_OFF         0x08        // Display OFF
#define LCD_DISPLAY_ON          0x0C        // Display on, cursor off
#define LCD_DISPLAY_ON_CURSOR   0x0E        // Display on, cursor on, no blink
#define LCD_FUNC_SET            0x28        // 4-bit mode, 2 lines, 5x8 font
#define LCD_INIT_8BIT           0x3         // 8-bit mode indicator
#define LCD_INIT_4BIT           0x2         // 4-bit mode selector
#define LCD_LINE1_ADDR          0x00        // DDRAM address for line 1
#define LCD_LINE2_ADDR          0xC0        // DDRAM address for line 2
#define LCD_CHARS_PER_LINE      16          // Characters per line (16x2 display)

typedef enum {
    LCD_CMD  = 0,    // Command mode
    LCD_DATA = 1    // Data mode
} lcd_mode_t;

void lcd_setup(void);
void lcd_write(uint8_t value, lcd_mode_t mode);
void lcd_clear(void);
void lcd_home(void);
void lcd_print(const char*);
void lcd_init(void);
uint32_t delay_to_cycles(uint32_t);

#endif // LCD_DRIVER_H