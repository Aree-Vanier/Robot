#include "Input.h"
#include <pt.h>
#include "Arduino.h"

int activeReg = 0;

int interval = 100;

void Input::init(){
}

int Input::thread(struct pt* pt){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      PT_WAIT_UNTIL(pt, millis()-timestamp > interval);
      this->periodic();
  }
  PT_END(pt);
  Serial1.begin(9600);
}


void Input::periodic(){
  Serial.println(Serial1.available());
  if(Serial1.available() > 0){
    Serial.println("Reading");
    Serial.write(Serial1.read());
  }  
}

//Output selected register
int Input::getRegister(int reg){
  return this->registers[reg];
}
