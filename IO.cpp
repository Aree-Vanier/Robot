#include "IO.h"
#include <Arduino.h>
#include "Socket.h"

Socket sock;

//Used to control output pins


void decToBin(int num, int bits, int* out){
  num = abs(num);
  for(int i=bits-1; i>=0; i--){
    if(num/pow(2, i)>=1){
      out[bits-1-i]=1;
      num -= pow(2,i);
    } else{
      out[bits-1-i]=0;
    }
  }
}

void IO::init(Socket& s){
  sock = s;
  pinMode(this->enablePin, OUTPUT);
  digitalWrite(this->enablePin, LOW);
  pinMode(this->regPins[0], INPUT);
  pinMode(this->regPins[1], INPUT);
  for(int i = 0; i<this->numPinCount; i++){
    pinMode(this->numPins[i], OUTPUT);
    digitalWrite(this->numPins[i], LOW);
  }
  pinMode(flipPin, OUTPUT);
  digitalWrite(this->flipPin, LOW);
}

void IO::loop(){
//  Enabled indicator
  if(sock.getEnabled()){
    digitalWrite(0, LOW);
  } else{
    digitalWrite(0, HIGH);
  }

  
}
