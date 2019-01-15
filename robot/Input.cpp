#include "Input.h"
#include <pt.h>
#include "Arduino.h"

const int inPinCount = 6;
//Pins used to send value, inPin[0] is the positive/negative flag
const int inPins[inPinCount] = {27,22,23,24,25,26};
const int outPinCount = 2;
const int outPins[outPinCount] = {30,31};
const int interval = 250;

int activeReg = 0;

void Input::init(){
  //Initialize pins
  for(int i = 0; i<inPinCount; i++){
    pinMode(inPins[i], INPUT);
  }
  for(int i = 0; i<outPinCount; i++){
    pinMode(outPins[i], OUTPUT);
  }
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
}


void Input::periodic(){
  //Read previous register
  Serial.print(activeReg+"\t");
  byte in[6];
  for(int i = 0; i<inPinCount; i++){
    in[i] = digitalRead(inPins[i]);
    Serial.print(inPins[i]);
    Serial.print(":");
    Serial.print(digitalRead(inPins[i]));
    Serial.print(" ");
  }

  int val = 0;
  for(int i = 1; i<inPinCount-1; i++){
    val+=pow(2,i)*in[inPinCount-1-i];
  }
  //If negative flag is true
  if(in[0]==1){
    val*=-1;
  }

  Serial.print("\t"+val);

  //Save the register value
  this->registers[activeReg]=val;

  //Select next register
//  activeReg ++;
  if(activeReg == 0){digitalWrite(outPins[0], LOW);digitalWrite(outPins[1], LOW);}
//  if(activeReg == 1){digitalWrite(outPins[0], LOW);digitalWrite(outPins[1], HIGH);}
//  if(activeReg == 2){digitalWrite(outPins[0], HIGH);digitalWrite(outPins[1], LOW);}
//  if(activeReg == 3){digitalWrite(outPins[0], HIGH);digitalWrite(outPins[1], HIGH);}
  
  //Wait for interval to get result
  Serial.println();
}

//Output selected register
int Input::getRegister(int reg){
  return this->registers[reg];
}
