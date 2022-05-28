#include <Arduino.h>
#include "tlc_config.h"


class Tlc5940
{
  private:
    uint8_t tlc_GSData[NUM_TLCS * 24];
  public:
    Tlc5940();
    void init(uint16_t initialValue = 0);
    void clear(void);
    uint8_t update(void);
    void set(uint8_t channel, uint16_t value);
    uint16_t get(uint8_t channel);
    void setAll(uint16_t value);
#if VPRG_ENABLED
    void setAllDC(uint8_t value);
#endif
#if XERR_ENABLED
    uint8_t readXERR(void);
#endif

};
