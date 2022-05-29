# TLC5940 Library for ESP32

## Known issues



## ToDo's 
- Use direct Hardware Timer instead of the ledc library
- Implement Dot Correction (VPREG) Enabled 
- Implement Error detection (XERR)
- Use SPI-Interface (Currently direct implementated)
  - Support SPI3
  - Support Status Infromation Output
    - Note: Status Infromation Output is MISO (Master In Slave Out signal). The TLC Output is the Sout-Pin this pin has to be connected to the HSPI_

