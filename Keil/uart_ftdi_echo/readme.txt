Interfacing FTDI chip with TM4C123GH6PM microcontroller to perform echo test

Link:
	FTDI: https://ftdichip.com/products/ft232rl/#

Summary:
	Characters typed into the console connected to FTDI are echoed back via UART port of the microcontroller.
	The on-board green LED is turned on during the echo operation.
	UART1 and GPIO ports B and F of the microcontroller are utilised.

Connections:
    FTDI Rx  - Tiva PB1
    FTDI Tx  - Tiva PB0
    FTDI GND - Tiva GND

Software tools:
    OS    - Windows 11
    PuTTY - SSH client