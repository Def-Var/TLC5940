# TLC5940 Library for ESP32

This Library is for the TLC5940 and the ESP32. Unfortunately the library from Paul Stoffregen claims to  support the ESP32 but the library is only for avr or teensy. This library can only handle the ESP32. An in-deep description is on my blog: https://def-var.net/tutorial/tutorial-esp32-and-tlc5940/

## Pinout

WARNING: Pinout can change. Software is in alpha Version

| ESP32 | TLC5940 |
| --- | --- |
| D14 / HSPI_SCLK | SCLK |
| D15 / HSPI_CS | XLAT | 
| D13 / HSPI_MOSI | SIN | 
| D27 / PWM Pin | GSCLK | 
| D12 / HSPI_MISO | - | 
| D26 / PWM Pin | BLANK | 

The pinout can be changed but bare in mind that the SCLK and SIN pins are connected to the right SPI port. The HSPI_MISO is connected to the BLANK pin but this is not relay nessasary, because this pin is not used for the data transfer. The BLANK pin and the GSCLK pin are used for the Operation for the IC. 

In future releases I want to use the Status Infromation Output from the TLC5940. This means that I have to connect the HSPI_MISO to the Sout pin. The current connection is because Paul Stoffregen has done this connection as well. It is not a great Idea but if you don't use the HSPI_MISO for the Sout than you can use the HSPI_MISO like an default GPIO pin. 

## Known issues

- [ ] [Sometimes the bits are shifted by 1 or 2 digits (flickering)](https://github.com/Def-Var/TLC5940/issues/1)


## ToDo's 
- [ ] Use direct Hardware Timer instead of the ledc library
- [ ] Implement Dot Correction (VPREG) Enabled 
- [ ] Implement Error detection (XERR)
- [x] Fast Output On / Off (BLANK HIGH) 
- [X] Use SPI-Interface (Currently direct implementated) 
  - [ ] Support SPI3
  - [ ] Support Status Infromation Output
    - Note: Status Infromation Output is MISO (Master In Slave Out signal). The TLC Output is the Sout-Pin this pin has to be connected to the HSPI_

## Features

### Fast Output

In `tlc->init()` is the timer default enabled.
```
// Starts Timer 
tlc->enable() 
// Sets Blank to High (Disables Output) LED Off 
tlc->disable()
```
