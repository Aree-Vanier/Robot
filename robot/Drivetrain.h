#ifndef Drivetrain_h
#define Drivetrain_h

#include <pt.h>
#include "Controller.h"

class Drivetrain{
  public:
    //Constructor, requires 4 analog pins and 4 digital pins
    Drivetrain(int analog[4], int digital[4]);
    //Set drivetrian speeds
    void drive(float lSpeed, float rSpeed);
    //Called to handle the threading
    int thread(struct pt* pt);
    //Function called regularly by thread
    void periodic();
  private:
    //Controllers
    Controller* fl;
    Controller* fr;
    Controller* br;
    Controller* bl;
};

#endif
