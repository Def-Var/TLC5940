# TLC5940 Library for ESP32

This Library is for the TLC5940 and the ESP32. Unfortunately the library from Paul Stoffregen claims to  support the ESP32 but the library is only for avr or teensy. This library can only handle the ESP32.

## Pinout

| ESP32 | TLC5940 |
| --- | --- |
| D14 / HSPI_SCLK | SCLK |
| D15 / HSPI_CS | XLAT | 
| D13 / HSPI_MOSI | SIN | 
| D27 / PWM Pin | GSCLK | 
| D12 / HSPI_MISO | BLANK | 

The pinout can be changed but bare in mind that the SCLK and SIN pins are connected to the right SPI port. The HSPI_MISO is connected to the BLANK pin but this is not relay nessasary, because this pin is not used for the data transfer. The BLANK pin and the GSCLK pin are used for the Operation for the IC. 

In future releases I want to use the Status Infromation Output from the TLC5940. This means that I have to connect the HSPI_MISO to the Sout pin. The current connection is because Paul Stoffregen has done this connection as well. It is not a great Idea but if you don't use the HSPI_MISO for the Sout than you can use the HSPI_MISO like an default GPIO pin. 

## Known issues

### Issue 1
Sometimes the bits are shifted by 1 or 2 digits


## ToDo's 
- [ ] Use direct Hardware Timer instead of the ledc library
- [ ] Implement Dot Correction (VPREG) Enabled 
- [ ] Implement Error detection (XERR)
- [X] Use SPI-Interface (Currently direct implementated) 
  - [ ] Support SPI3
  - [ ] Support Status Infromation Output
    - Note: Status Infromation Output is MISO (Master In Slave Out signal). The TLC Output is the Sout-Pin this pin has to be connected to the HSPI_

