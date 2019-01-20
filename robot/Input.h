#ifndef Input_h
#define Input_h

#include "Drivetrain.h"

class Input{
    public:
      void init(Drivetrain *d);
      int thread(struct pt* pt);
      void periodic();
      int getRegister(int reg);
      enum Register {
        L_AXIS=0,
        R_AXIS=1,
        TOGGLE=2,
        };
    private:
      int registers[4];
      Drivetrain* drivetrain;
};

#endif
