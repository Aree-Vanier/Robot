#include "Arduino.h"
#include "Controller.h"

//This class is used to interface with the motor controllers

//Constuctor, requires an analog pin and a digital pin
Controller::Controller(int speedPin, int directionPin){
  //Assign locals
  this->speedPin = speedPin;
  this->directionPin = directionPin;
  
  //Setup pins
  pinMode(speedPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  
  //Set speed
  this->speed = 0;
}

//Truth table
//pin1 -> speed pin (analog)
//pin2 -> direction pin (digital)
//if reverse, pin 2 is true, speed is 255-speed

//Called to set the targe speed
void Controller::set(float percent){
  //Cap percentage under 100%
  if(percent > 1) percent = 1;
  if(percent < -1) percent = -1;

  //Map percentage to PWM value
  this->targetSpeed = (int) map(percent*100, -100,100,-255,255);
}

//Get the current speed, returns current speed
double Controller::getSpeed(){
  return(map(speed, -255,255,-100,100)/100);
}

//Stop the controller instantly
void Controller::stop(){
  //Set both pins to low to force a stop
  digitalWrite(this->directionPin, LOW);
  digitalWrite(this->speedPin, LOW);
}

//Called regulaly to smooth acceleration
void Controller::drive(){
  //If the gap is smaller than acceleration, just max the speed
  if(abs(this->speed-this->targetSpeed) < this->accel){
      this->speed = this->targetSpeed;
  }
  //If it's too slow, accelerate
  if(this->speed < this->targetSpeed){
      this->speed+=this->accel;
  }
  //If it's too fast, decelerate
  if(this->speed > this->targetSpeed){
      this->speed-=this->accel;
  }

  //If the speed is 0, hard stop
  if(this->speed == 0){
    digitalWrite(this->directionPin, LOW);
    digitalWrite(this->speedPin, LOW);
  }
  //If the speed is positive, drive forward
  if(this->speed > 0){
      digitalWrite(this->directionPin, LOW);
      analogWrite(this->speedPin, this->speed);
  }
  //If the speed is negative, reverse
  else{
      digitalWrite(this->directionPin, HIGH);
      analogWrite(this->speedPin, 255-abs(this->speed));
  }
}
