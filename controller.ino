#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include "Page.h"

//Network Info
const char* ssid = "BELL995";
const char* password = "A1FDE7E6";

boolean enabled = false;

//Create the servers
WebSocketsServer webSocket = WebSocketsServer(81);

//Create the webpage
Page page;

//Used to control output pins
void  stringToBin(String str, int bits, int* out){
  int num = str.toInt();
  for(int i=bits-1; i>=0; i--){
    if(num/pow(2, i)>=1){
      out[bits-1-i]=1;
      num -= pow(2,i);
    } else{
      out[bits-1-i]=0;
    }
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  if(type == WStype_TEXT){
    String in = "";
    for(int i = 0; i<length; i++){
      in+=(char)payload[i];
    }
    Serial.println(in);
    if(in=="en"){
      enabled = true;
      char* c = "|en|";
      webSocket.broadcastTXT(c, sizeof(c));
    }
    if(in=="di"){
      enabled = false;
      char* c = "|di|";
      webSocket.broadcastTXT(c, sizeof(c));
    }
  }
  if(type == WStype_CONNECTED){
    char* c = "conn";
    webSocket.broadcastTXT(c, sizeof(c));
    delay(50);
    if(enabled) c="|en|";
    else c="|di|";
    webSocket.broadcastTXT(c, sizeof(c));
    Serial.println("Connected");
  }
  if(type == WStype_DISCONNECTED){
    enabled = false;
    Serial.println("Disconnected");
  }
}



void setup() {
  Serial.begin(115200);

  pinMode(0, OUTPUT);

  //Connect to WiFi
  WiFi.begin(ssid, password);
  //Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  //Declare connection and IP
  Serial.println("WiFi Connected!");
  Serial.print("IP is: ");
  Serial.println(WiFi.localIP());

  //Initialise the webpage
  page.init();
  
  webSocket.begin();

  //Handle input
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  page.loop();
  webSocket.loop();
  if(Serial.available() > 0){
    char c[] = {(char)Serial.read()};
    webSocket.broadcastTXT(c, sizeof(c)); 
  }
  //Enabled indicator
  if(enabled){
    digitalWrite(0, LOW);
  } else{
    digitalWrite(0, HIGH);
  }
}
