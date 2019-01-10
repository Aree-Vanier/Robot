#ifndef Drivetrain_h
#define Drivetrain_h

#include "Controller.h"

class Drivetrain{
    public:
        Drivetrain(int analog[4], int digital[4]);
        drive(int lStick, int rStick);
        drive(float lSPeed, float rSpeed);
    private:
      Controller* fl;
      Controller* fr;
      Controller* br;
      Controller* bl;
};

#endif
