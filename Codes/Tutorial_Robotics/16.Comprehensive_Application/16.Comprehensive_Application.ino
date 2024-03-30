#include <IRremote.h>
#include <FastLED.h>
#define RECV_PIN 19
int Ultrasonic_Pin = 27, Button_pin = 18, Buzzer_pin = 33, QTI_L = 39, QTI_R = 36, state_value = 1;
int distance, state_L, state_N, QTI_Max, Speed = 160;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  pinMode(QTI_L, INPUT);
  pinMode(QTI_R, INPUT);
  irrecv.enableIRIn();
  ledcSetup(2, 2000, 8);
  ledcAttachPin(Buzzer_pin, 2);
  pinMode(RECV_PIN, INPUT);
  pinMode(Button_pin,INPUT);
  for (int i = 12; i <= 15; i++) {
    ledcSetup(i, 255, 8);
    ledcAttachPin(i, i);
  }
  while (digitalRead(Button_pin) == 1);
}
void Get_Distance() {
  pinMode(Ultrasonic_Pin, OUTPUT);
  digitalWrite(Ultrasonic_Pin, HIGH);
  delayMicroseconds(20);
  digitalWrite(Ultrasonic_Pin, LOW);
  pinMode(Ultrasonic_Pin, INPUT);
  int Time_Echo_us = pulseIn(Ultrasonic_Pin, HIGH);
  distance = Time_Echo_us / 58;
}

void Motor(int L1, int L2 , int R1, int R2) {
  ledcWrite(12, L1);
  ledcWrite(13, L2);
  ledcWrite(14, R1);
  ledcWrite(15, R2);
}
void Tracking(){
  if (state_value == 3){
    QTI_Max = digitalRead(QTI_L) * 2 + digitalRead(QTI_R); 
    if (QTI_Max == 0){
      Motor(Speed, 0, Speed, 0);
    }
    else if (QTI_Max == 1){
      Motor(0, Speed, 0, Speed / 2);
    }
    else if (QTI_Max == 2){
      Motor(0, Speed / 2, 0, Speed);
    }
    else if (QTI_Max == 3){
      Motor(0, Speed + 40, 0, Speed + 40);
    }
  }
}
void Obstacle_Avoidance() {
  if (state_value == 2){
    Get_Distance();
    if (distance < 20) {
      Motor(Speed, 0, 0, Speed);
    }
    else {
      Motor(0, Speed, 0, Speed);
    }
  }
}
void IR_remote_control() {
  if (state_N == 0xFFA25D) {
    state_value = 1;
  }
  else if (state_N == 0xFF629D){
    state_value = 2;
  }
  else if (state_N == 0xFFE21D){
    state_value = 3;
  }
  if (state_value == 0){
    Motor(0, 0, 0, 0);
  }
  Remote_Move();
  
}
void Remote_Move(){
  if (state_value == 1){
    switch (state_N) {
      case 0xFF18E7:
        Motor(0, Speed, 0, Speed);
        break;
      case 0xFF4AB5:
        Motor(Speed, 0, Speed, 0);
        break;
      case 0xFF10EF:
        Motor(Speed, 0, 0, Speed);
        break;
      case 0xFF5AA5:
        Motor(0, Speed, Speed, 0);
        break;
    }
  }
}
void loop() {
  Serial.println(state_value);
  if (irrecv.decode(&results)) {
    if (results.value == 0xFFFFFFFFF) {
      state_N = state_L;
    }
    else {
      state_N = results.value;
      state_L = results.value;
      delay(100);
    }
    IR_remote_control();
    irrecv.resume();
  }
  else {
    Motor(0, 0, 0, 0);
  }
  Obstacle_Avoidance();
  Tracking();
  delay(150);
}
