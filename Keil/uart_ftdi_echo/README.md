# UART FTDI Echo Project

## Project Configuration

1. Manage runtime environment: Select **CMSIS:Core** and **Device:Startup**
2. Options for Target <...>: Choose **Stellaris ICDI** under "Use" in Debug tab.

## Description

This project interfaces an [FTDI chip](https://ftdichip.com/products/ft232rl/#) with the TM4C123GH6PM microcontroller to perform an echo test.

## Summary

- Characters typed into the console connected to FTDI are echoed back via the UART port of the microcontroller.
- The on-board green LED is turned on during the echo operation.
- UART1 and GPIO ports B and F of the microcontroller are utilised.

## Connections

| FTDI Pin | Tiva Pin |
|----------|----------|
| Rx       | PB1      |
| Tx       | PB0      |
| GND      | GND      |

## Software Tools

- OS: Windows 11
- PuTTY: SSH client
