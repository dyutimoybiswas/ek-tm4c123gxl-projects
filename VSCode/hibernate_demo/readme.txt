Project demonstrating hibernation module.

RTC match wake and pin wake are demonstrated in this example. 
Pressing SW1 configures RTC match wake subject to seconds delay as configured by the user in hibernate_mode.h, and reenables hibernate after match occurs.
Pressing SW2 configures pin wake, as it is connected to (WAKE)' pin.
Hibernation status as well as cause of wake is displayed in serial console via UART0.

Either SW1 or SW2 should be defined in tm4c_toolchain.cmake while executing the project.
The board should be power cycled before flashing each time.