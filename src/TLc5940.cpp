#include"Tlc5940.h"

void Tlc5940::init(uint16_t initialValue)
{
    /* Pin Setup */
    pinMode(HSPI_CS, OUTPUT);
    pinMode(HSPI_MISO, OUTPUT);
    pinMode(HSPI_MOSI, OUTPUT);
    pinMode(HSPI_SCLK, OUTPUT);  

    // SPI Setup
    this->spi = new SPIClass(HSPI);
    this->spi->begin();
    this->spi->beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE3));

    // Timer Stuf 
    pinMode(GSCLK_PIN, OUTPUT);  
    ledcSetup(GSCLK_TIMER, GSCLK_FREQ, GSCLK_TIMER_RESULUTION);
    ledcAttachPin(GSCLK_PIN, GSCLK_TIMER);
    ledcWrite(GSCLK_TIMER, 1);

    digitalWrite(HSPI_MOSI, LOW); // leave blank high (until the timers start)
    // double xlat = 976;
    // ledcSetup(1, xlat, 8);
    // ledcAttachPin(HSPI_CS, 1);
    // ledcWrite(1, 2);

    ledcSetup(2, BLANK_FREQ, 12);
    ledcAttachPin(HSPI_MISO, 2);
    ledcWrite(2, 2);
    
#if VPRG_ENABLED
    #error VPRG -> DOT correction not supported (yet)
#endif
#if XERR_ENABLED
    #error XERR -> Error detection not supported (yet)
#endif
    
    setAll(initialValue);
    update();
}

Tlc5940::Tlc5940(uint8_t amount_tlc) {
    this->amount_tlc = amount_tlc;
}

uint8_t Tlc5940::update(){
  for (int tlc_num = 0; tlc_num < NUM_TLCS; tlc_num++) {

    digitalWrite(HSPI_CS, HIGH);
    for (int i = 0; i < 2; i++);
    digitalWrite(HSPI_CS, LOW);

    for (int tlc_index = 0; tlc_index < 24; tlc_index++) {
      byte b = this->tlc_GSData[tlc_num*24 + tlc_index];
      this->spi->transfer(b);
    }
  }

  return 0;
}

void Tlc5940::set(uint8_t channel, uint16_t value) {
    byte index8 = (3 * 16 - 1) - channel;
    uint8_t *index12p = this->tlc_GSData + ((((uint16_t)index8) * 3) >> 1);
    if (index8 & 1) { // starts in the middle
                      // first 4 bits intact | 4 top bits of value
        *index12p = (*index12p & 0xF0) | (value >> 8);
                      // 8 lower bits of value
        *(++index12p) = value & 0xFF;
    } else { // starts clean
                      // 8 upper bits of value
        *(index12p++) = value >> 4;
                      // 4 lower bits of value | last 4 bits intact
        *index12p = ((uint8_t)(value << 4)) | (*index12p & 0xF);
    }
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

void Tlc5940::disable(){
    ledcWrite(2, 4095);
}

void Tlc5940::enable(){
    ledcWrite(2, 2);
}

void Tlc5940::clear(void)
{
    setAll(0);
}

uint8_t* Tlc5940::getGSData() {
    return this->tlc_GSData;
}