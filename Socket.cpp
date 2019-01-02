#include "Socket.h"
#include <Arduino.h>
#include <WebSocketsServer.h>

//Create the servers
WebSocketsServer webSocket = WebSocketsServer(81);

void Socket::webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  Serial.println("An event occured");
  if(type == WStype_TEXT){
    String in = "";
    for(int i = 0; i<length; i++){
      in+=(char)payload[i];
    }
    Serial.println(in);
    if(in=="en"){
      this->enabled = true;
      char* c = "|en|";
      webSocket.broadcastTXT(c, sizeof(c));
    }
    if(in=="di"){
      this->enabled = false;
      char* c = "|di|";
      webSocket.broadcastTXT(c, sizeof(c));
    }
  }
  if(type == WStype_CONNECTED){
    char* c = "conn";
    webSocket.broadcastTXT(c, sizeof(c));
    delay(50);
    if(this->enabled) c="|en|";
    else c="|di|";
    webSocket.broadcastTXT(c, sizeof(c));
    Serial.println("Connected");
  }
  if(type == WStype_DISCONNECTED){
    this->enabled = false;
    Serial.println("Disconnected");
  }
}

Socket::Socket() : WebSocketsServer(81) {
  Serial.println("Setup");
}

void Socket::init(){
  Serial.println("Initialised");
  webSocket.begin();
}

void Socket::loop(){
  webSocket.loop();
  if(Serial.available() > 0){
    char c[] = {(char)Serial.read()};
    webSocket.broadcastTXT(c, sizeof(c)); 
  }
}
