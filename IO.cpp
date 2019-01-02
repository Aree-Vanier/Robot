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

int binToDec(int* bits, int bitCount){
  int out = 0;
  for(int i = 0; i<bitCount; i++){
    out+=pow(2,i)*bits[bitCount-1-i];
  }
  return out;
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
  int reg[2] = {digitalRead(regPins[0]), digitalRead(regPins[1])};
  int selected = sock.getRegister(binToDec(reg, 2));
  int pins[this->numPinCount];
  decToBin(selected, this->numPinCount, pins);
  for(int i = 0; i<this->numPinCount; i++){
    Serial.print(i);
    Serial.print(": ");
    Serial.print(pins[i]);
    Serial.print("\t");
    digitalWrite(this->numPins[i], pins[i]);
  }
  Serial.println();
}
