# Robot
This repository contains the code used to run a simple robot powered by an Arduino Mega, with networking provided by a ESP8266

# How it works
The ESP2866 serves a webpage with a simple input interface. The embedded javascript creates a webSocket connection with the ESP. From there, the data is stored and can be sent to the Mega.
There are 4 registers that can be selected, each conating 6 bits of data (-31 to 31), as well as a pin to enable the robot.
