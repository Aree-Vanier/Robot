#include <ESP8266WebServer.h>


class Page{
  public:
    void init();
    void loop();
  private:
    ESP8266WebServer* server;
};
