## About
Projects in this folder were run using **Keil uVision ver. 5.33** on **Windows 11 OS**.

## Project Configuration

### Manage Runtime Environment
1. Select **CMSIS:Core** and **Device:Startup**.

### Options for Target
1. In the **Debug** tab, choose **Stellaris ICDI** under "Use".
2. In **C/C++**:
	- Choose **C11** (language C)
	- Enable **MISRA compatible** (Warnings)
	- Add the `inc` folder of the project to the include path.

## Project List

- **[adc_temperature_measurement](#adc_temperature_measurement)**  
  Monitors temperature of the board at specified intervals.  
  - Blue LED = standby  
  - Red LED = unsafe range  
  - Green LED = safe range

- **[adc_voltage_measurement](#adc_voltage_measurement)**  
  Measures voltage between 0 to 3.3 V by connecting potentiometer output to PE2 pin.

- **[external_reset](#external_reset)**  
  To trigger reset externally using RST pin.

- **[freq_division](#freq_division)**  
  Demo to customize system frequency and blink on-board blue LED at different frequencies.

- **[generate_custom_delay](#generate_custom_delay)**  
  Generates maximum delay of 1.00352 seconds, minimum delay of 4.096 milliseconds when multiplier (m) = 1.  
  Define either `SECONDS` or `MILLISECONDS` to generate a suitable delay. Adjust seconds/milliseconds value in header file.  
  Maximum checked delay = 5 minutes (300 seconds).

- **[generate_signal](#generate_signal)**  
  Generates signal in port F (blue LED).  
  Design: Ton = Toff (square wave). Time period = 2 * Ton. Ton is loaded in ILR of timer.

- **[GPIO_switch_LED](#GPIO_switch_LED)**  
  Toggling switch turns on/off LED blinking.

- **[gptm_demo](#gptm_demo)**  
  Demo project to show count-up, count-down modes in periodic configuration of general-purpose timer.

- **[pwm_example](#pwm_example)**  
  Blinks on-board blue LED based on duty cycle of PWM signal.

- **[pwm_LED_fading](#pwm_LED_fading)**  
  Controls brightness of on-board red LED from minimum to maximum.

- **[reset_indicator](#reset_indicator)**  
  Flashes on-board green LED to indicate microcontroller reset.

- **[rgb_colors](#rgb_colors)**  
  Sets 3 colors (turquoise, magenta, orange) in RGB on-board LED using PWM.  
  Define either `TURQUOISE`, `MAGENTA`, or `ORANGE` to see the corresponding color.

- **[rgb_pattern](#rgb_pattern)**  
  Displays pattern of colors on RGB LEDs.

- **[switch_portf](#switch_portf)**  
  Demonstrates switch action.  
  Press and hold on-board switches to see LED turn on, release to turn off.  
  - SW1 = blue LED  
  - SW2 = red LED

- **[switch_toggle](#switch_toggle)**  
  Press switch to start blinking LED, press again to turn off.  
  - SW1 = blue LED  
  - SW2 = red LED

- **[uart_ftdi_echo](#uart_ftdi_echo)**  
  Refer to [README.md](./uart_ftdi_echo/README.md).

- **[watchdog_demo](#watchdog_demo)**  
  Watchdog timer loads a value inside the while loop and counts down to 0.  
  If value reaches 0 before an operation is completed, the interrupt is triggered.  
  In this example, the event is a delay function.  
  - For normal operation, green LED is on  
  - For interrupt, red LED is on  
  Define `MILLISECONDS` or `SECONDS` to generate delay as per need.
