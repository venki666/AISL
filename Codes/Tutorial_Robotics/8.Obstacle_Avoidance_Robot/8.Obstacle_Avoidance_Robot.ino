int distance = 0, Ultrasonic_Pin = 27, Button_pin = 18;

void setup() {
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
void loop() {
  Get_Distance();
  if (distance < 20) {
    Motor(255, 0,0, 255);
  }
  else
  {
    Motor(0,255, 0, 255);
  }
}
