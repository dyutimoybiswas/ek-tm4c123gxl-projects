## About
Projects in this folder were run using **Microsoft Visual Studio Code** in **Debian OS**.

## Project Configuration
Execute the run_project script to generate flashable binary files.
Use a tool like TI Uniflash to flash the binary into the board and observe the output.


## Project List

### [blinky](blinky/)
Code to blink on-board RGB LEDs in intervals of some delay, in the order Red, Blue and Green.

### [hibernate_demo](hibernate_demo/)
Project demonstrating hibernation module.

RTC match wake and pin wake are demonstrated in this example.  
Pressing SW1 configures RTC match wake subject to seconds delay as configured by the user in hibernate_mode.h, and reenables hibernate after match occurs.  
Pressing SW2 configures pin wake, as it is connected to (WAKE)' pin.  
Hibernation status as well as cause of wake is displayed in serial console via UART0.

Either SW1 or SW2 should be defined in tm4c_toolchain.cmake while executing the project.  
The board should be power cycled before flashing each time.

### [PWM_demo](PWM_demo/)
Code to generate colors using on-board RGB LEDs and PWM.

### [systick_demo](systick_demo/)
Generate delay of 1 second/millisecond using systick timer.  
Define SECOND/MILLISECOND as per need in tm4c_toolchain.cmake file.

### [timer_demo](timer_demo/)
Code to blink the on-board blue LED by configuring a timer in 16-bit periodic count-down mode.

### [UART_echo](UART_echo/)
Code to echo text entered into the console using UART.