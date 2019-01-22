#include <pt.h>
#include "Input.h"
#include "Drivetrain.h"

static struct pt inputStruct;
static struct pt drivetrainStruct;

int aPins[4] = {2,5,4,3};
int dPins[4] = {42,45,44,43};

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
}
