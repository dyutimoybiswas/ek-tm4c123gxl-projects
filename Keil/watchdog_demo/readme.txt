Watchdog timer loads a value inside the while loop and counts down to 0. If value reaches 0 before
an operation is completed, the interrupt is triggered. In this example the event is a delay function. For normal
operation, green LED is on, for interrupt red LED is on.
Define MILLISECONDS or SECONDS to generate delay as per need.
