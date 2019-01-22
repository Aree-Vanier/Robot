#ifndef Page_h
#define Page_h
#include <pt.h>

#include <Arduino.h>

class Page{
  public:
    //Initialise
    void init();
    //Called to handle the threading
    int thread(struct pt* pt);
    //Function call regularly by thread
    void periodic();
  private:
};

#endif
