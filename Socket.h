#ifndef Socket_h
#define Socket_h
#include <WebSocketsServer.h>


class Socket: private WebSocketsServer {
  public:
    Socket();
    void init();
    void loop();
    bool enabled;
  private:
    void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
};

#endif
