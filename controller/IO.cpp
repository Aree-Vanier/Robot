#include "IO.h"
#include <Arduino.h>
#include "Socket.h"
#include <pt.h>

//This class is used to handle communications between the ESP8266 and the Mega

//Socket reference
Socket sock;

//Interval(ms) between thread iterations
int IOInterval = 10;

//Initialise, needs socket reference
void IO::init(Socket& s){
  //Set socket ref
  sock = s;
  //Setup onboard LED (used to indicated enabled status)
  pinMode(this->enablePin, OUTPUT);
  digitalWrite(this->enablePin, LOW);
}

//Called to handle the threading
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


//Function call regularly by thread
void IO::periodic(){
  //Light enable LED
  if(sock.getEnabled()) digitalWrite(this->enablePin, LOW);
  else digitalWrite(this->enablePin, HIGH);
  //If there is a request
  if(Serial.available() > 0){
    //Prep the output
    String out = "D";
    out += sock.getRegister(0);
    out += "|";
    out += sock.getRegister(1);
    out += "|";
    out += sock.getRegister(2);
    //Send the ouput
    Serial.println(out);

    //Clear the serial buffer
    while(Serial.available() > 0){
      Serial.read();
    }
  }
}
