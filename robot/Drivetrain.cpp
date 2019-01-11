#include "Drivetrain.h"
#include "Controller.h"
#include "Arduino.h"

Drivetrain::Drivetrain(int analog[4], int digital[4]){
  this->fl = new Controller(analog[0], digital[0]);
  this->fr = new Controller(analog[1], digital[1]);
  this->bl = new Controller(analog[2], digital[2]);
  this->br = new Controller(analog[3], digital[3]);
}

void Drivetrain::drive(int lStick, int rStick){
  //Map inputs to percentages
  float lSpeed = map(lStick, -31, 31, -100, 100)/100;
  float rSpeed = map(rStick, -31, 31, -100, 100)/100;
  this->drive(lSpeed, rSpeed);
}

void Drivetrain::drive(float lSpeed, float rSpeed){
  Serial.println(lSpeed, rSpeed);

  //Set left motors
  this->fl->set(lSpeed);
  this->bl->set(lSpeed);
  //Set right motors
  this->fr->set(rSpeed);
  this->br->set(rSpeed);
}
