#include "Arduino.h"
#include "Controller.h"

Controller::Controller(int speedPin, int directionPin){
    this->speedPin = speedPin;
    this->directionPin = directionPin;
    pinMode(speedPin, OUTPUT);
    pinMode(directionPin, OUTPUT);
    this->speed = 0;
}
//Truth table
//pin1 -> speed pin (analog)
//pin2 -> direction pin (digital)
//if reverse, pin 2 is true, speed is 255-speed

void Controller::set(float percent){
//    Serial.println("IN: "+(String) percent);
    if(percent > 1) percent = 1;
    if(percent < -1) percent = -1;
//    Serial.println(percent);
    this->targetSpeed = (int) map(percent*100, -100,100,-255,255);
//    Serial.println(this->targetSpeed);
}

double Controller::getSpeed(){
    return(map(speed, -255,255,-100,100)/100);
}

void Controller::stop(){
    digitalWrite(this->directionPin, LOW);
    digitalWrite(this->speedPin, LOW);
}

void Controller::drive(){
//    Serial.println(this->targetSpeed);
    if(abs(this->speed-this->targetSpeed) < this->accel){
        this->speed = this->targetSpeed;
    }
    if(this->speed < this->targetSpeed){
        this->speed+=this->accel;
    }
    if(this->speed > this->targetSpeed){
        this->speed-=this->accel;
    }


    if(this->speed == 0){
      digitalWrite(this->directionPin, LOW);
      digitalWrite(this->speedPin, LOW);
    }
    if(this->speed > 0){
        digitalWrite(this->directionPin, LOW);
        analogWrite(this->speedPin, this->speed);
    }
    else{
        digitalWrite(this->directionPin, HIGH);
        analogWrite(this->speedPin, 255-abs(this->speed));
    }
}
