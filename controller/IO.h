#ifndef IO_h
#define IO_h
#include <pt.h>

#include "Socket.h"

class IO{
  public:
    void init(Socket& s);
    void periodic();
    int thread(struct pt* pt);
  private:
    const int enablePin = 0;//Pin used to inform arduino of enable status
};

#endif
