## uDMA (micro direct memory access) demo

## Description
UART0 is used to echo console input back to the serial monitor. DMA is used in basic mode for UART Tx, bypassing the processor, while Rx is handled using the receive timeout interrupt. Using DMA for Tx reduces processing overhead, allowing the processor to focus on other tasks.

### Limitation
Using DMA for UART Rx drains the FIFO buffer, preventing the Rx timeout interrupt from triggering. This makes it impossible to detect end-of-message for variable-length data, leading to missed or incomplete reads.


## UART
- determine USB port allocated to the board using `ls /dev/cu.usb*`
- open serial monitor using `screen /dev/cu.usbXXX 115200`. 
### Note:
Enter usb obtained from previous step, and adjust baud rate if using other value. Press `control(^)+A` followed by `K` to quit `screen`.