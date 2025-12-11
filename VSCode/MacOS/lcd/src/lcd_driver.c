#include "lcd_driver.h"

// Helper to calculate SysCtlDelay_argument from milliseconds
uint32_t delay_to_cycles(uint32_t delay_ms)
{
    return (SysCtlClockGet() / 3000) * delay_ms;
}

void lcd_setup(void)
{
    // Set system clock
    SysCtlClockSet(SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);    // enable port B
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
        // wait till peripheral is enabled
    }

    // Configure output pins
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, LCD_RS_PIN | LCD_E_PIN | LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN);
}

// Pulse the Enable pin to latch data
void lcd_pulse_enable(void)
{
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E_PIN, LCD_E_PIN);
    SysCtlDelay(delay_to_cycles(5));
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_E_PIN, 0);
    SysCtlDelay(delay_to_cycles(5));
}

void lcd_send_nibble(uint8_t nibble)
{
    uint8_t data = (nibble & 0x0F) << 2;    // lower 4 bits of nibble, left-shifted since GPIO pin 2 onwards used
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_D4_PIN | LCD_D5_PIN | LCD_D6_PIN | LCD_D7_PIN, data);
    SysCtlDelay(delay_to_cycles(1));
    lcd_pulse_enable();
}

// Send a byte (command or data) in 4-bit mode (two nibbles)
void lcd_write(uint8_t value, lcd_mode_t mode)
{
    uint8_t upper_nibble, lower_nibble;
    
    // Set RS pin based on mode
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RS_PIN, mode ? LCD_RS_PIN : 0);
    SysCtlDelay(delay_to_cycles(10));

    upper_nibble = value >> 4;
    lcd_send_nibble(upper_nibble);
    SysCtlDelay(delay_to_cycles(10));

    lower_nibble = value & 0x0F;
    lcd_send_nibble(lower_nibble);
    SysCtlDelay(delay_to_cycles(10));
    SysCtlDelay(delay_to_cycles(5));
}

void lcd_clear(void)
{
    lcd_write(LCD_CLEAR, LCD_CMD);
    SysCtlDelay(delay_to_cycles(10));
}

// Return cursor to home position
void lcd_home(void)
{
    lcd_write(LCD_HOME, LCD_CMD);
    SysCtlDelay(delay_to_cycles(10));
}

void lcd_print(const char* str)
{
    uint8_t position = 0;
    
    while (*str)
    {
        if (position == LCD_CHARS_PER_LINE)
        {
            lcd_write(LCD_LINE2_ADDR, LCD_CMD);
            SysCtlDelay(delay_to_cycles(10));
            position = 0;
        }
        
        lcd_write((uint8_t)(*str), LCD_DATA);
        SysCtlDelay(delay_to_cycles(5));
        str++;
        position++;
    }
}

// Initialize LCD display
void lcd_init(void)
{
    lcd_setup();
    SysCtlDelay(delay_to_cycles(200));
    
    // First nibble, sent 3 times for robust initialization
    GPIOPinWrite(GPIO_PORTB_BASE, LCD_RS_PIN, 0);
    for (uint8_t i = 0; i < 3; ++i) {
        lcd_send_nibble(LCD_INIT_8BIT);
        SysCtlDelay(delay_to_cycles(50));
    }
    
    lcd_send_nibble(LCD_INIT_4BIT);
    SysCtlDelay(delay_to_cycles(50));

    lcd_write(LCD_FUNC_SET, LCD_CMD);
    SysCtlDelay(delay_to_cycles(20));

    lcd_write(LCD_DISPLAY_OFF, LCD_CMD);
    SysCtlDelay(delay_to_cycles(20));

    lcd_write(LCD_ENTRY_MODE, LCD_CMD);
    SysCtlDelay(delay_to_cycles(20));

    // Clear display twice to ensure clean DDRAM
    for (uint8_t i = 0; i < 2; ++i) {
        lcd_clear();
        SysCtlDelay(delay_to_cycles(100));
    }

    lcd_write(LCD_DISPLAY_ON, LCD_CMD);
    SysCtlDelay(delay_to_cycles(100));

    lcd_write(LCD_HOME, LCD_CMD);
    SysCtlDelay(delay_to_cycles(200));
}

int main(void) {
    lcd_init();

    // Modify text to display here
    lcd_print("Quick Brown Fox Jumps Hazy Veldt");

    return 0;
}
