#ifndef IO_h
#define IO_h
#include <pt.h>

#include "Socket.h"

//This class is used to handle communications between the ESP8266 and the Mega
class IO{
  public:
    //Initialise, needs socket reference
    void init(Socket& s);
    //Called to handle the threading
    int thread(struct pt* pt);
    //Function call regularly by thread
    void periodic();
  private:
    //Pin used to inform arduino of enable status
    const int enablePin = 0;
};

#endif
