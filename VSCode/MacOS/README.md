## Project Configuration
- Put the extracted software kit contents in this directory.
- Install [docker](https://docker.com).
- Connect the board to the computer.
- Execute the [run_project.sh](run_project.sh) script with project name as argument. This generates flashable binaries in a `build` directory within the project directory, and flashes the `elf` file to the board.

## Debugging
- Remove `exit` from openocd command options in [run_project.sh](run_project.sh)
- Execute [run_project.sh](run_project.sh) script as mentioned above
- In a new terminal window, execute `arm-none-eabi-gdb <project_name>.elf`
- Inside `gdb`, run below commands in order:
    - `target remote localhost:3333` (to connect to board)
    - `load` (to flash the binary)
    - `monitor reset halt`
- Now that debugging session is ready, set breakpoints and continue to debug

## Project List

### [blinky](blinky/)
Code to blink on-board RGB LEDs at intervals of ~1 sec, in the order Red, Green and Blue.
### [loopback](loopback/)
Code to test loopback on supported communication protocols
### [lcd](lcd/)
Refer corresponding [README](lcd/README.md)
### [udma](udma/)
Refer corresponding [README](udma/README.md)
### [freertos_blinky](freertos_blinky/)
Demonstrates FreeRTOS **v8.2.3** (bundled with TivaWare) using binary semaphores to synchronize 3 tasks that blink the on-board RGB LED in R→G→B sequence. Each LED: 300ms on, 300ms off (configurable).
