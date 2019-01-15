#include "IO.h"
#include <Arduino.h>
#include "Socket.h"

Socket sock;

//Used to control communications

void IO::init(Socket& s){
  sock = s;
  pinMode(this->enablePin, OUTPUT);
  digitalWrite(this->enablePin, LOW);
}

void IO::loop(){
  Serial.println(sock.getRegister(0));
  //Enable pin
  if(sock.getEnabled()) digitalWrite(this->enablePin, LOW);
  else digitalWrite(this->enablePin, HIGH);
}
