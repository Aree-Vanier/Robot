#include "Drivetrain.h"
#include "Controller.h"
#include "Arduino.h"

int drivetrainInterval = 5;

Drivetrain::Drivetrain(int analog[4], int digital[4]){
  this->fl = new Controller(analog[0], digital[0]);
  this->bl = new Controller(analog[1], digital[1]);
  this->fr = new Controller(analog[2], digital[2]);
  this->br = new Controller(analog[3], digital[3]);
}

void Drivetrain::drive(float lSpeed, float rSpeed){
//  Serial.println(lSpeed, rSpeed);

  //Set left motors
  this->fl->set(-lSpeed);
  this->bl->set(-lSpeed);
  //Set right motors
  this->fr->set(rSpeed);
  this->br->set(rSpeed);
}

int Drivetrain::thread(struct pt* pt){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      PT_WAIT_UNTIL(pt, millis()-timestamp > drivetrainInterval);
      this->periodic();
  }
  PT_END(pt);
}

void Drivetrain::periodic(){
      this->fl->drive();
      this->fr->drive();
      this->bl->drive();
      this->br->drive();
}
