#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include "Page.h"
#include "Socket.h"

//Network Info
const char* ssid = "BELL995";
const char* password = "A1FDE7E6";


//Create the webpage
Page page;

Socket socket;

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
  
  //Initialise the socket
  socket.init();
}

void loop() {
  page.loop();
  socket.loop();
  Enabled indicator
  if(socket.enabled){
    digitalWrite(0, LOW);
  } else{
    digitalWrite(0, HIGH);
  }
}
