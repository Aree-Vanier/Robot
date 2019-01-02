#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

//Network Info
const char* ssid = "BELL995";
const char* password = "A1FDE7E6";

boolean enabled = false;

//Create the servers
ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(81);

char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width">
  <title>JS Bin</title>
  <style>
    body{
      background-color:black;
      color:white;
      margin:0px;
    }
    /* Header */
    .container{    
      margin: auto;
      width: 80%;
      padding: 5px 20%;
      overflow:hidden;
      border-bottom:5px solid white;
    }

    .beside{
      float:left;
      width:45%;
    }

    #enable{
      border:none;
      font-size:20px;
      background-color:white;
      padding:5px 10%;
    }

    .status{
      font-size:25px;
      margin-top:2px;
      transform:translate(-20px,0px);
    }

    #enable.true{
      background-color:limegreen;
      color:white;
    }
    #enable.false{
      background-color:red;
      color:white;
    }
    #enable.locked{
      background-color:gray;
      color:black;
    }

    #status.true{
      color:limegreen;
    }
    #status.false{
      color:red;
    }

    /* Controls */
    input{
      margin-left:20%;
      display:block;
      width:60%;
    }
  </style>
  <script>
    var Socket;
    function init(){
       Socket = new WebSocket("ws://"+window.location.hostname+":81/");
       Socket.onmessage = function(event){
        console.log(event.data);
        if(event.data=="conn"){
          document.getElementById("status").innerHTML="Connected";
          document.getElementById("status").className="true";
        }
        if(event.data=="|en|"){
          document.getElementById("enable").innerHTML="Disable";
          document.getElementById("enable").className="true";
        }
        if(event.data=="|di|"){
          document.getElementById("enable").innerHTML="Enable";
          document.getElementById("enable").className="false";
        }
       }
    }
    function update(element){
      console.log(element.value);
      Socket.send(element.value)
    }

    function enable(){
      if(document.getElementById("enable").className=="false"){
        Socket.send("en");
      } else{
        Socket.send("di");
      }
    }
  </script>
</head>
<body onload="init()">
  <div class="container">
    <div class="beside status">Status: <span id="status" class="false">Disconnected</span></div>
    <div class="beside"><button id="enable" class="locked" onclick="enable()">Enable</button></div>
  </div>
  <br/>
  <input type="range" style="float:left" id="slider"/>
</body>
</html>
)=====";

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

  //Setup hadlers
  server.on("/", [](){server.send_P(200, "text/html", webpage);});
  //Start the servers
  server.begin();
  webSocket.begin();

  //Handle input
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  server.handleClient();
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
