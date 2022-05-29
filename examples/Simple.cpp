#include <Arduino.h>
#include <Tlc5940.h>
/*************************************************** 
Example fot the TLC5940 Lib. 
 ****************************************************/


Tlc5940 *tlc = NULL;

int global_index = 0;
int pwm_value = 0;
int mode = 0;

void setup() {

  Serial.begin(9600);

  tlc = new Tlc5940();
  tlc->init();

}



void loop() {
    // Mode 0: Turn on 1 Channel by one 
  if (mode == 0) {
    if (global_index == 0) 
      tlc->set(NUM_TLCS * 16 -1, 0);
    else
      tlc->set(global_index - 1, 0);

    tlc->set(global_index, 0xFFF);

    global_index++;

    // Reset and Change mode when done
    if (global_index == 48) {
      global_index = 0;
      mode = 1;
    }
    Serial.println(global_index);
    // Mode 1: Turn on all channels with increasing PWM vlaues
  } else if (mode == 1) {
    tlc->setAll(pwm_value);
    pwm_value+= 10;

    // Reset and Change mode when done
    if (pwm_value > 4096) {
      pwm_value = 0;
      mode = 0;
      tlc->clear();
    }
  }

  // update TLC
  tlc->update();

  // print GSData to Serial in HEX format
  for (int index = 0; index < 24*3; index++) {
    Serial.print(tlc->getGSData()[index], HEX);
  }
  Serial.println();

  // Delay
  delay(500);
}
