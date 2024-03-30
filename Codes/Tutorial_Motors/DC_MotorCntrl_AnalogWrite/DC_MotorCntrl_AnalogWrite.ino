#include <Arduino.h>
#include "esp32-hal-ledc.h"

int SpeedStep = 1;
int Speed = 0;
#define MOTORIN1 16
#define MOTORIN2 17
void setup() {
 analogWriteFrequency(915); // set frequency to 10 KHz for LED pin
 //analogWriteFrequency(MOTORIN2, 915); // set frequency to 10 KHz for LED pin
  // Set resolution for a specific pin
  analogWriteResolution(10);
}

void loop() {

  analogWrite(MOTORIN1, 512);
  analogWrite(MOTORIN2, 0);
  delay(5000);
  
  analogWrite(MOTORIN1, 0);
  analogWrite(MOTORIN2, 0);
  delay(1000);
  
  analogWrite(MOTORIN1, 0);
  analogWrite(MOTORIN2, 512);
  delay(5000);
  
  analogWrite(MOTORIN1, 0);
  analogWrite(MOTORIN2, 0);
  delay(1000);
}
