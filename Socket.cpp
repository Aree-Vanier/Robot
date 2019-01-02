#include "Socket.h"
#include <Arduino.h>
#include <WebSocketsServer.h>

bool enabled;

WebSocketsServer s = WebSocketsServer(81);


void enable(){
    enabled = true;
    char* c = "|en|";
    s.broadcastTXT(c, sizeof(c));
}

void disable(){
    enabled = false;
    char* c = "|di|";
    s.broadcastTXT(c, sizeof(c));
}

void onConnect(){
    char* c = "conn";
    s.broadcastTXT(c, sizeof(c));
    delay(50);
    if(enabled) c="|en|";
    else c="|di|";
    s.broadcastTXT(c, sizeof(c));
    Serial.println("Connected");
}

void onDisconnect(){
    disable();
    Serial.println("Disconnected");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  Serial.println("An event occured");
  if(type == WStype_TEXT){
    String in = "";
    for(int i = 0; i<length; i++){
      in+=(char)payload[i];
    }
    Serial.println(in);
    if(in=="en") enable();
    if(in=="di") disable();
  }
  if(type == WStype_CONNECTED) onConnect();
  if(type == WStype_DISCONNECTED) onDisconnect();
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

int Socket::getRegister(int reg){
  return this->registers[reg];
}

bool Socket::getEnabled(){
  return enabled;
}

bool Socket::setEnabled(bool b){
  enabled = b;
}
