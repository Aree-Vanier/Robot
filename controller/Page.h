#ifndef Page_h
#define Page_h
#include <pt.h>

#include <Arduino.h>

class Page{
  public:
    void init();
    int thread(struct pt* pt);
    void periodic();
  private:
};

#endif
