#include "IO.h"
#include <Arduino.h>
#include "Socket.h"
#include <pt.h>

Socket sock;

int IOInterval = 100;

//Used to control communications

void IO::init(Socket& s){
  sock = s;
  pinMode(this->enablePin, OUTPUT);
  digitalWrite(this->enablePin, LOW);
}

int IO::thread(struct pt* pt){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      PT_WAIT_UNTIL(pt, millis()-timestamp > IOInterval);
      this->periodic();
  }
  PT_END(pt);
}



void IO::periodic(){
  //Enable pin
  if(sock.getEnabled()) digitalWrite(this->enablePin, LOW);
  else digitalWrite(this->enablePin, HIGH);
  if(Serial.available() > 0){
    Serial.println("D0|125|255");
    
    while(Serial.available() > 0){
      Serial.read();
    }
  }
}
