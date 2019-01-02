#include "Socket.h"
#include <Arduino.h>
#include <WebSocketsServer.h>

bool enabled;

WebSocketsServer s = WebSocketsServer(81);

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  Serial.println("An event occured");
  if(type == WStype_TEXT){
    String in = "";
    for(int i = 0; i<length; i++){
      in+=(char)payload[i];
    }
    Serial.println(in);
    if(in=="en"){
      enabled = true;
      char* c = "|en|";
      s.broadcastTXT(c, sizeof(c));
    }
    if(in=="di"){
      enabled = false;
      char* c = "|di|";
      s.broadcastTXT(c, sizeof(c));
    }
  }
  if(type == WStype_CONNECTED){
    char* c = "conn";
    s.broadcastTXT(c, sizeof(c));
    delay(50);
    if(enabled) c="|en|";
    else c="|di|";
    s.broadcastTXT(c, sizeof(c));
    Serial.println("Connected");
  }
  if(type == WStype_DISCONNECTED){
    enabled = false;
    Serial.println("Disconnected");
  }
}

void Socket::init(){

  s.onEvent(webSocketEvent);
  
  s.begin();

  s.onEvent(webSocketEvent);
}

void Socket::loop(){
  s.loop();
  if(Serial.available() > 0){
    char c[] = {(char)Serial.read()};
    s.broadcastTXT(c, sizeof(c)); 
  }
}

bool Socket::getEnabled(){
  return enabled;
}

bool Socket::setEnabled(bool b){
  enabled = b;
}
