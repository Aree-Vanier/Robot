#ifndef IO_h
#define IO_h

#include "Socket.h"

class IO{
  public:
    void init(Socket& s);
    void loop();
  private:
    static const byte numPinCount = 5;
    static const byte regCount = 4;
    //Numerating of pins
    const int enablePin = 13;//Pin used to inform arduino of enable status
    const int regPins[2] = {14,16};//Pins used to select register
    const int numPins[numPinCount] = {15,2,0,4,5};//Pins used to transmit selected register value
    const int flipPin = 12;//Pin used to indicated positive/negative
};

#endif
