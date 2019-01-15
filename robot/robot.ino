#include <pt.h>
#include "Input.h"

static struct pt input;

Input i;

void setup() {
  Serial.begin(9600);
  PT_INIT(&input);
}

void loop() {
  i.thread(&input);
}
