#ifndef Input_h
#define Input_h

#include "Drivetrain.h"

class Input{
  public:
    //Initialise the input, needs a drivetrain pointer
    void init(Drivetrain *d);
    //Called to handle the threading
    int thread(struct pt* pt);
    //Function called regularly by thread
    void periodic();
    //Output selected register
    int getRegister(int reg);
  private:
    int registers[4]; // Local copy of registers
    Drivetrain* drivetrain; // Pointer to drivetrain
};

#endif
