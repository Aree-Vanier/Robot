#include <pt.h>
#include "Input.h"
#include "Drivetrain.h"

//Analog pins
int aPins[4] = {2,5,4,3};
//Dgital pins
int dPins[4] = {42,45,44,43};

//Create input handler
Input input;
static struct pt inputStruct;

//Create drivetrain
Drivetrain drive(aPins, dPins);
static struct pt drivetrainStruct;

void setup() {
  Serial.begin(9600);
  //Initialise threads
  PT_INIT(&inputStruct);
  PT_INIT(&drivetrainStruct);
  //Initialise input
  input.init(&drive);
}

void loop() {
  //Run threads
  input.thread(&inputStruct);
  drive.thread(&drivetrainStruct);
}
