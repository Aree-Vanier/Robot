#include <pt.h>
#include "Input.h"
#include "Drivetrain.h"

static struct pt inputStruct;
static struct pt drivetrainStruct;

int aPins[4] = {2,3,4,5};
int dPins[4] = {42,43,44,45};

Input input;
Drivetrain drive(aPins, dPins);

void setup() {
  Serial.begin(9600);
  PT_INIT(&inputStruct);
  PT_INIT(&drivetrainStruct);
  input.init(&drive);
}

void loop() {
  input.thread(&inputStruct);
  drive.thread(&drivetrainStruct);
//  input.periodic();
//  drive.periodic();
}
