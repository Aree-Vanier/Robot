#include "Socket.h"
#include <Arduino.h>
#include <WebSocketsServer.h>

bool enabled;

WebSocketsServer s = WebSocketsServer(81);

int registers[4] = {0,15,16,31};


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

void setRegister(String in){
  int reg = (in.substring(3,4)).toInt();
  in.remove(0,in.indexOf("|")+1);
  int value = in.toInt();
  registers[reg] = value;
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
    if(in.startsWith("REG")) setRegister(in);
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
  return registers[reg];
}

bool Socket::getEnabled(){
  return enabled;
}

bool Socket::setEnabled(bool b){
  enabled = b;
}
