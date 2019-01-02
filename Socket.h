#ifndef Socket_h
#define Socket_h
#include <WebSocketsServer.h>


class Socket {
  public:
    void init();
    void loop();
    bool getEnabled();
    bool setEnabled(bool b);
  private:
};

#endif
