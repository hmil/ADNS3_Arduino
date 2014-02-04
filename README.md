# ADNS3

This library provides support for ADNS-3xxx optical mouse sensors.
For now it works with ADNS-3030/3040 and maybe with others if you are lucky but
you can easily configure the lib to work with the whole ADNS-3xxx series. See
header file for more infos.

## Setup

Download the repo's archive and extract it to "*your_arduino_install_dir*/libraries/".
Then open ADNS.h and follow the instructions.

## Usage

Pins 1,2,3 and 4 should be SPI's SS, MISO, SCLK, MOSI. Check your device's datasheet
to make sure it is. Connect these pins to your board's [SPI pins](http://arduino.cc/en/Reference/SPI)

**Warning** : ADNS3XXX chips work on 3.3V so you should use something to protect it from Arduino's 5V output.
Also, the LED is sometimes powered by the chip, sometimes not, check the datasheet for application circuit recommandations.

The readMotion() method provides an abstract interface for motion measures
provided you specified the right MOTION_REG value (see header file).
Otherwise, use readRegister() and writeRegister() to access registers found in your device's datasheet.
