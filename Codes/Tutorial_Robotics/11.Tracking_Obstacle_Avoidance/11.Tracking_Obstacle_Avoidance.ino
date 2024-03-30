#include <FastLED.h>
int IR_L = 39, IR_R = 36, Ultrasonic_Pin = 27, Buzzer_pin = 33, Button_pin = 18;
int Time_Echo_us, distance, Speed = 160;
CRGB leds[6];

void Get_Distance(){
  pinMode(Ultrasonic_Pin, OUTPUT);
  digitalWrite(Ultrasonic_Pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(Ultrasonic_Pin, LOW);
  pinMode(Ultrasonic_Pin, INPUT);
  Time_Echo_us = pulseIn(Ultrasonic_Pin, HIGH);
  distance = Time_Echo_us / 58;
}

void setup() {
  pinMode(IR_L, INPUT);
  pinMode(IR_R, INPUT);
  ledcSetup(2, 2000, 8);
  ledcAttachPin(Buzzer_pin, 2);
  FastLED.addLeds<WS2812, 26, GRB>(leds, 6);
  FastLED.setBrightness(255);
  for (int i = 12; i <= 15; i++) {    
    ledcSetup(i, 255, 8);             
    ledcAttachPin(i, i);              
  }
  while (digitalRead(Button_pin) == 1);
}

void motor(int L1, int L2 , int R1, int R2) {
  ledcWrite(12, L1);
  ledcWrite(13, L2);
  ledcWrite(14, R1);
  ledcWrite(15, R2);
}

void Tracking() {
  int IR_value = digitalRead(IR_L) * 2 + digitalRead(IR_R);
  if (IR_value == 0) {
    motor(Speed, 0, Speed, 0);
  } else if (IR_value == 1) {
    motor(0, Speed, 0, Speed / 2);
  } else if (IR_value == 2) {
    motor(0, Speed / 2, 0, Speed);
  } else {
    motor(0, Speed + 40, 0, Speed + 40);
  }
}
void loop() {
  Get_Distance();
  if (distance < 10){
    motor(0, 0, 0, 0);
    fill_solid(leds, 6, CRGB::Red);
    FastLED.setBrightness(255);
    FastLED.show();
    ledcWriteTone(2, 262);
    delay(300);
    FastLED.setBrightness(0);
    FastLED.show();
    ledcWriteTone(2, 0);
    delay(300);
  }else{
    fill_solid(leds, 6, CRGB::Green);
    FastLED.setBrightness(255);
    FastLED.show();
    Tracking();
  }
}
