#include "Socket.h"
#include <Arduino.h>
#include <WebSocketsServer.h>
#include <pt.h>

//This class handles communications with the web socket

//Enabled flag
bool enabled;

//Create the server
WebSocketsServer s = WebSocketsServer(81);

//range is 0-255, so 125=0;
int registers[4] = {125,125,125,125};

//Interval(ms) between thread iterations
int sockInterval = 100;

//Enable the robot
void enable(){
    enabled = true;
    //Send enable flag to client
    char* c = "|en|";
    s.broadcastTXT(c, sizeof(c));
}

//Disable the robot
void disable(){
    enabled = false;
    //Send disable flag to client
    char* c = "|di|";
    s.broadcastTXT(c, sizeof(c));
}

//Called when a client connects
void onConnect(){
    //Send connection flag to cliend
    char* c = "conn";
    s.broadcastTXT(c, sizeof(c));
    
    delay(50);
   
    //Send enable/disable flag
    if(enabled) c="|en|";
    else c="|di|";
    s.broadcastTXT(c, sizeof(c));
    
    //Announce connection
    Serial.println("Connected");
}

//Called when client disconnects
void onDisconnect(){
    //Disable the robot
    disable();
    Serial.println("Disconnected");
}

//Set the register values
//In is formatted as REG#|###
void setRegister(String in){
  //Get target register from string
  int reg = (in.substring(3,4)).toInt();
  
  //Get value from string
  in.remove(0,in.indexOf("|")+1);
  int value = in.toInt();
  
  //Set register to value
  registers[reg] = value;
}

//Called when socket event occurs
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  //If a string is sent
  if(type == WStype_TEXT){
    //Get string
    String in = "";
    for(int i = 0; i<length; i++){
      in+=(char)payload[i];
    }
    //Call apropriate function
    if(in=="en") enable();
    if(in=="di") disable();
    if(in.startsWith("REG")) setRegister(in);
  }
  //Handle connect/disconnect
  if(type == WStype_CONNECTED) onConnect();
  if(type == WStype_DISCONNECTED) onDisconnect();
}

//Initialise the socket
void Socket::init(){
  //Set event handler
  s.onEvent(webSocketEvent);
  
  s.begin();
}

//Called to handle the threading
int Socket::thread(struct pt* pt){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      PT_WAIT_UNTIL(pt, millis()-timestamp > sockInterval);
      this->periodic();
  }
  PT_END(pt);
}

//Function called regularly by thread
void Socket::periodic(){
  //Loop the server
  s.loop();
}

//Get requested register, returns value of regsiters
int Socket::getRegister(int reg){
  return registers[reg];
}

//Get enabled status, returns enabled satus
bool Socket::getEnabled(){
  return enabled;
}

//Set enabled status
bool Socket::setEnabled(bool b){
  enabled = b;
}
