#include "Input.h"
#include <pt.h>
#include "Arduino.h"

int Input::thread(struct pt* pt, int interval){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      PT_WAIT_UNTIL(pt, millis()-timestamp > interval);
      this->periodic();
  }
  PT_END(pt);
}


void Input::periodic(){
  Serial.println("THREAD");
}
