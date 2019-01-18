#ifndef Socket_h
#define Socket_h
#include <WebSocketsServer.h>
#include <pt.h>


class Socket {
  public:
    void init();
    void periodic();
    bool getEnabled();
    bool setEnabled(bool b);
    int getRegister(int reg);
    int thread(struct pt* pt);
  private:
};

#endif
