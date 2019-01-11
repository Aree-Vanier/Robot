#ifndef Drivetrain_h
#define Drivetrain_h

#include "Controller.h"

class Drivetrain{
    public:
        Drivetrain(int analog[4], int digital[4]);
        void drive(int lStick, int rStick);
        void drive(float lSpeed, float rSpeed);
    private:
      Controller* fl;
      Controller* fr;
      Controller* br;
      Controller* bl;
};

#endif
