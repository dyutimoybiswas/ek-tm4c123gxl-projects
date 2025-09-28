## Project Configuration
- Put the extracted software kit contents in this directory.
- Install [docker](https://docker.com).
- Connect the board to the computer.
- Execute the [run_project.sh](run_project.sh) script with project name as argument. This generates flashable binaries in a `build` directory within the project directory, and flashes the `elf` file to the board.


## Project List

### [blinky](blinky/)
Code to blink on-board RGB LEDs in intervals of ~1 sec delay, in the order Red, Green and Blue.
