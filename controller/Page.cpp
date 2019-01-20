#include "Page.h"
#include <ESP8266WebServer.h>
#include <pt.h>

int pageInterval = 1000;

//==== Start of HTML ====
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
    var socket;
    function init(){
       socket = new WebSocket("ws://"+window.location.hostname+":81/");
       socket.onmessage = function(event){
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
      socket.send(element.value)
    }

    function enable(){
      if(document.getElementById("enable").className=="false"){
        socket.send("en");
      } else{
        socket.send("di");
      }
    }

    function sendReg(element, reg){
      console.log("REG"+reg+"|"+element.value);
      socket.send("REG"+reg+"|"+element.value);
    }
  </script>
</head>
<body onload="init()">
  <div class="container">
    <div class="beside status">Status: <span id="status" class="false">Disconnected</span></div>
    <div class="beside"><button id="enable" class="locked" onclick="enable()">Enable</button></div>
  </div>
  <br/>
  <input type="range" style="float:left" oninput="sendReg(this,0)" max="0" min="250">
  <input type="number" style="float:left" onChange="sendReg(this,1)"/>
  <input type="number" style="float:left" onChange="sendReg(this,2)"/>
  <input type="number" style="float:left" onChange="sendReg(this,3)"/>
</body>
</html>
)=====";

//===== End of HTML =====


ESP8266WebServer server;
    
void Page::init(){
  //Setup hadlers
  server.on("/", [](){server.send_P(200, "text/html", webpage);});
  //Start the servers
  server.begin();
}

int Page::thread(struct pt* pt){
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1){
      timestamp = millis();
      PT_WAIT_UNTIL(pt, millis()-timestamp > pageInterval);
      this->periodic();
  }
  PT_END(pt);
}

void Page::periodic(){
  server.handleClient();
}
