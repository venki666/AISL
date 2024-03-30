#include <IRremote.h>
#define RECV_PIN 19
IRrecv irrecv(RECV_PIN);
decode_results results;
int state_L, state_N, Speed = 255, Button_pin = 18;
void setup() {
  Serial.begin(9600);
  pinMode(Button_pin, INPUT);
  irrecv.enableIRIn();
  pinMode(RECV_PIN, INPUT);
  for (int i = 12; i <= 15; i++) { 
    ledcSetup(i, 255, 8);          
    ledcAttachPin(i, i);           
  }
  while (digitalRead(Button_pin) == 1);
}

void Motor(int L1, int L2 , int R1, int R2) {
  ledcWrite(12, L1);
  ledcWrite(13, L2);
  ledcWrite(14, R1);
  ledcWrite(15, R2);
}
void IR_remote_control() {
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
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xFFFFFFFFF) {
      state_N = state_L;
    }
    else {
      state_N = results.value;
      state_L = results.value;
    }
    IR_remote_control();
    irrecv.resume();
  }
  else {
    Motor(0, 0, 0, 0);
  }
  delay(150);
}
