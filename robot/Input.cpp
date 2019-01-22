#include "Input.h"
#include <pt.h>
#include "Arduino.h"
#include "Drivetrain.h"


//Interval(ms) between thread iterations
int intputInterval = 10;

//Initialise the input, needs a drivetrain pointer
void Input::init(Drivetrain *d){
  this->drivetrain = d;
  Serial2.begin(9600);
}

//Called to handle the threading
int Input::thread(struct pt* pt){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      Serial.println(timestamp);
      PT_WAIT_UNTIL(pt, millis()-timestamp > intputInterval);
      this->periodic();
  }
  PT_END(pt);
}


//Function called regularly by thread
void Input::periodic(){
  //Ping the ESP8266
  Serial2.print("Ping");
  delay(5);
  //If there is a reply
  if(Serial2.available()>0){
    //Get message
    String in = "";
    while(Serial2.available()){
      in+=char(Serial2.read());
    }
    //If it starts with D (signifies Data)
    if(in.startsWith("D")){
      //Parse the input
      in = in.substring(0, in.lastIndexOf("\n"))+":";
      in = in.substring(in.lastIndexOf("\n")+2, in.indexOf(":")+1);
      //Set register values
      this->registers[0] = in.substring(0,in.indexOf("|")).toInt()-125;
      this->registers[1] = in.substring(in.indexOf("|")+1, in.lastIndexOf("|")).toInt()-125;
      this->registers[2] = in.substring(in.lastIndexOf("|")+1, in.indexOf(":")).toInt()-125;
    }
    //Print values to main serial (for debug)
    Serial.print(this->registers[0]);Serial.print("\t");Serial.print(this->registers[1]);Serial.print("\t");Serial.print(this->registers[2]);Serial.print("\n");
  }

  //Drive the robot
  this->drivetrain->drive((float) map(this->registers[0], -125, 125, -100, 100)/100, (float) map(this->registers[1], -125, 125, -100, 100)/100);
  
}

//Output selected register
int Input::getRegister(int reg){
  return this->registers[reg];
}
