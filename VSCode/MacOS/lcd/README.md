# LCD display example

## Hardware
- LCD display (16x2, module - RG1602A)
- breadboard
- 10k potentiometer/ 10k + 1k resistors
- 100 ohms resistor for anode
- jumper wires & connecting cables

## Smoke test
Below configuration tests basic working of the LCD module:
| Pin | Signal |
|-----|--------|
| VSS | GND |
| VDD | 5V (board pin preferred) |
| V0 | 0.4V (resistor bridge/ potentiometer) |
| A | 5V through 100 ohms resistor|
| K | GND |

after connecting as above, first row of LCD display should display boxes. If using potentiometer, adjust brightness as per need.

## Description
This project demonstrates displaying custom text on LCD display. Modify the text to display in `main()` function. See [example](example.gif) for demonstration.

### Configuration
This project uses LCD in 4-bit mode and GPIO port B for connecting to LCD

### Connections
| Pin | Signal |
|-----|--------|
| VSS | GND |
| VDD | 5V (board pin preferred)|
| RS | PB0 |
| RW | GND |
| E | PB1 |
| D4 | PB2 |
| D5 | PB3 |
| D6 | PB4 |
| D7 | PB5 |
| V0 | 0.4V (resistor bridge/ potentiometer)|
| A | 5V through 100 ohms resistor|
| K | GND |