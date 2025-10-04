## Project Configuration
- Put the extracted software kit contents in this directory.
- Install [docker](https://docker.com).
- Connect the board to the computer.
- Execute the [run_project.sh](run_project.sh) script with project name as argument. This generates flashable binaries in a `build` directory within the project directory, and flashes the `elf` file to the board.


## Project List

### [blinky](blinky/)
Code to blink on-board RGB LEDs at intervals of ~1 sec, in the order Red, Green and Blue.
### [i2c_loopback](i2c_loopback/)
Configure I2C peripheral 2 (pins A6 & A7) in loopback mode for testing. `Master` mode sends 
data (`yellow`) which is read by slave, followed by a `slave` write of `magenta`. Upon read, the
data is written to on-board LEDs for display. Master and slave read/write occurs at an interval
of ~1 sec.
