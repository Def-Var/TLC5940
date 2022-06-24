
#ifndef TLC_CONFIG_H
#define TLC_CONFIG_H


#define HSPI_MISO 12 // BLANK
#define HSPI_MOSI 13 // SIN
#define HSPI_SCLK 14 // SCLK 
#define HSPI_CS   15 // XLAT 

#define GSCLK_PIN 27
#define GSCLK_FREQ 10e6
#define GSCLK_TIMER 0
#define GSCLK_TIMER_RESULUTION 1

#define BLANK_PIN 26
#define BLANK_FREQ 2441
#define BLANK_HIGH 1
#define BLANK_RESULUTION 15



#ifndef NUM_TLCS
#define NUM_TLCS  3
#endif

#endif