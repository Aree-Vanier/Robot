#ifndef Socket_h
#define Socket_h
#include <WebSocketsServer.h>
#include <pt.h>


class Socket {
  public:
    //Initialise the socket
    void init();
    //Called to handle the threading
    int thread(struct pt* pt);
    //Function called regularly by thread
    void periodic();
    //Get enabled status, returns enabled satus
    bool getEnabled();
    //Set enabled status
    bool setEnabled(bool b);
    //Get requested register, returns value of regsiters
    int getRegister(int reg);
  private:
};

#endif
