#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include "Page.h"
#include "Socket.h"
#include "IO.h"

//Network Info
const char* ssid = "LDSB";
const char* password = "19812114D38DDDSDFVOPMJEW98452985HF587349Y6T73HTG89H";


//Create the webpage
Page page;

Socket socket;

IO io;

void setup() {
  Serial.begin(115200);

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

  //Initialise IO system
  io.init(socket);
}

String temp[4] = {"test", "test", "Test", "test"};

void loop() {
  page.loop();
  socket.loop();
  io.loop();
}
