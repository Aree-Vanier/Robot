#ifndef IO_h
#define IO_h

#include "Socket.h"

class IO{
  public:
    void init(Socket& s);
    void loop();
  private:
    const int enablePin = 0;//Pin used to inform arduino of enable status
};

#endif
