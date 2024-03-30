#include <ESP32Servo.h>
 
Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32
 
int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 13;
#define BUTTON_PIN   27
boolean oldState;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
  // using default min/max of 500us and 2400us
  // different servos may require different min/max settings
  // for an accurate 0 to 180 sweep
}
 
void loop() {
  boolean newState = digitalRead(BUTTON_PIN);
  
   if((newState == LOW) && (oldState == HIGH)) {
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    pos += 30;
    if(pos>180) pos = 0;
   }
   oldState = newState;
}
