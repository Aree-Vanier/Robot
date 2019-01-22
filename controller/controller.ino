#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <pt.h>
#include "Page.h"
#include "Socket.h"
#include "IO.h"
#include "config.h"

//Network Info
const char* ssid = SSID;
const char* password = PASSWORD;

//Create the webpage
Page page;
static struct pt PageStruct;
//Create the socket
Socket socket;
static struct pt SocketStruct;
//Create the IO system
IO io;
static struct pt IOStruct;


void setup() {
  Serial.begin(9600);

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

void loop() {
  //Run each thread
  page.thread(&PageStruct);
  socket.thread(&SocketStruct);
  io.thread(&IOStruct);
}
