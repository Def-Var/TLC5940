
#ifndef TLC_CONFIG_H
#define TLC_CONFIG_H


#define HSPI_MISO 12 // SIN
#define HSPI_MOSI 13 // BLANK
#define HSPI_SCLK 14 // SCLK 
#define HSPI_CS   15 // XLAT 

#define GSCLK_FREQ 4e6

#define BLANK_FREQ 976
#define BLANK_HIGH 2
#define BLANK_RESULUTION 12



#ifndef NUM_TLCS
#define NUM_TLCS  3
#endif

#endif