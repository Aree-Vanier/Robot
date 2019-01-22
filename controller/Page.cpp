#include "Page.h"
#include <ESP8266WebServer.h>
#include <pt.h>

//This is a class used entirely to store the HTML and code to run the webpage, so it doesn't clog up other files

//Interval(ms) between thread iterations
int pageInterval = 1000;

//The JS is partially documented (Read at own risk)
//==== Start of HTML ====
char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width">
  <title>Gregbot 9000</title>
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
      margin-bottom:100px !important;
    }
    
    input.vertical{
      -webkit-appearance: slider-vertical;
      width:20%;
      margin:0;
      height:300px;
    }
  </style>
  <script>
    var socket;
    var msgCount = 0;
    var lastMsg = "";
    function init(){
       //Create the socket           Point at own port 81
       socket = new WebSocket("ws://"+window.location.hostname+":81/");
       socket.onmessage = function(event){
        console.log(event.data);
         //If the message announces connection
        if(event.data=="conn"){
          document.getElementById("status").innerHTML="Connected";
          document.getElementById("status").className="true";
        }
         //If the message announces enabled
        if(event.data=="|en|"){
          document.getElementById("enable").innerHTML="Disable";
          document.getElementById("enable").className="true";
        }
         //If the message annouces disabled
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
    
    //Toggle the enable button
    function enable(){
      if(document.getElementById("enable").className=="false"){
        socket.send("en");
      } else{
        socket.send("di");
      }
    }
    
    //Send register value
    function sendReg(element, reg){
      //Deadzone
      msgCount++;
      if(Math.abs(125-element.value) <= 10){
        element.value = 125;
      }
      if(msgCount > 5 || element.value == 125){
        msgCount = 0;
        var msg = "REG"+reg+"|"+element.value;
        if(msg!=lastMsg){
          console.log(msg);
          socket.send("REG"+reg+"|"+element.value);
          lastMsg = msg;
        }
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
  <input type="range" class="vertical" style="float:left;margin-left:20%" oninput="sendReg(this,0)" max="250" min="0" step="5">
  <input type="range" class="vertical" style="float:right;margin-right:20%" oninput="sendReg(this,1)" max="250" min="0" step="5">
  <input type="range" style="float:left" oninput="sendReg(this,2)" max="250" min="0" step="5">
</body>
</html>
)=====";
//===== End of HTML =====

//Web server
ESP8266WebServer server;

//Setup page
void Page::init(){
  //Setup hadlers
  server.on("/", [](){server.send_P(200, "text/html", webpage);});
  //Start the servers
  server.begin();
}

//Called to handle the threading
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

//Function call regularly by thread
void Page::periodic(){
  server.handleClient();
}
