#include "Drivetrain.h"
#include "Controller.h"
#include "Arduino.h"

//This class is used as a wrapper for the controllers

//Interval(ms) between thread iterations
int drivetrainInterval = 5;

//Constructor, requires 4 analog pins and 4 digital pins
Drivetrain::Drivetrain(int analog[4], int digital[4]){
  this->fl = new Controller(analog[0], digital[0]);
  this->bl = new Controller(analog[1], digital[1]);
  this->fr = new Controller(analog[2], digital[2]);
  this->br = new Controller(analog[3], digital[3]);
}

//Set drivetrian speeds
void Drivetrain::drive(float lSpeed, float rSpeed){
  //Set left motors
  this->fl->set(-lSpeed);
  this->bl->set(-lSpeed);

  //Set right motors
  this->fr->set(rSpeed);
  this->br->set(rSpeed);
}


//Called to handle the threading
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

//Function called regularly by thread
void Drivetrain::periodic(){
  //Update the motors
  this->fl->drive();
  this->fr->drive();
  this->bl->drive();
      this->br->drive();
}
