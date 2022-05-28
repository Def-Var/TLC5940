#include"Tlc5940.h"

void Tlc5940::init(uint16_t initialValue)
{
    /* Pin Setup */
    pinMode(HSPI_CS, OUTPUT);
    pinMode(HSPI_MISO, OUTPUT);
    pinMode(HSPI_MOSI, OUTPUT);
    pinMode(HSPI_SCLK, OUTPUT);  
    
#if VPRG_ENABLED
    #error VPRG -> DOT correction not supported (yet)
#endif
#if XERR_ENABLED
    #error XERR -> Error detection not supported (yet)
#endif
    digitalWrite(HSPI_MOSI, LOW); // leave blank high (until the timers start)
    setAll(initialValue);
    update();

    // Timer Stuf 

    double x = 4.0e6;

    ledcSetup(0, GSCLK_FREQ, 1);
    ledcAttachPin(27, 0);
    ledcWrite(0, 1);
    
    // double xlat = 976;
    // ledcSetup(1, xlat, 8);
    // ledcAttachPin(HSPI_CS, 1);
    // ledcWrite(1, 2);

    ledcSetup(2, BLANK_FREQ, 12);
    ledcAttachPin(HSPI_MOSI, 2);
    ledcWrite(2, 2);
}

Tlc5940::Tlc5940() {}

uint8_t Tlc5940::update(){
    ledcDetachPin(HSPI_CS);

  

  // hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_CS);

  for (int tlc_num = 0; tlc_num < NUM_TLCS; tlc_num++) {

    digitalWrite(HSPI_CS, HIGH);
    for (int i = 0; i < 2; i++);
    digitalWrite(HSPI_CS, LOW);

    for (int tlc_index = 0; tlc_index < 24; tlc_index++) {
      // hspi->transfer(buff[tlc_num*24 + tlc_index]);
      byte b = this->tlc_GSData[tlc_num*24 + tlc_index];
      for (int byte_index = 7; byte_index > -1; byte_index--) {
        digitalWrite(HSPI_SCLK, LOW);
        digitalWrite(HSPI_MISO, (b >> byte_index) & 1);
        for (int i = 0; i < 2; i++);
        digitalWrite(HSPI_SCLK, HIGH);
        for (int i = 0; i < 2; i++);
      }
    }
  }

  //for(int i=0; i < (sizeof buff); i++) {
  //  hspi->transfer(buff[i]);
  // }
  // hspi->end();

  // digitalWrite(HSPI_CS, HIGH);
  // for (int i = 0; i < 20; i++);
  // digitalWrite(HSPI_CS, LOW);

  ledcAttachPin(HSPI_CS, 1);
  return 0;
}

void Tlc5940::setAll(uint16_t value) {
{
    byte firstByte = value >> 4;
    byte secondByte = (value << 4) | (value >> 8);
    byte *p = this->tlc_GSData;
    while (p < this->tlc_GSData + NUM_TLCS * 24) {
        *p++ = firstByte;
        *p++ = secondByte;
        *p++ = (byte)value;
    }
}
}