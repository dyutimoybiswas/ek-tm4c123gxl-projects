## About
This directory contains loopback tests for different communication protocols supported in Tiva C

## Project List
### [i2c_loopback](i2c_loopback/)
Configure I2C peripheral 2 (pins E4 & E5) in loopback mode for testing. `Master` mode sends 
data (`yellow`) which is read by slave, followed by a `slave` write of `magenta`. Upon read, the
data is written to on-board LEDs for display. Master and slave read/write occurs at an interval
of ~1 sec.