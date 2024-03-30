int Button_pin = 18, Photodiode_L = 35, Photodiode_R = 34;
void setup() {
  Serial.begin(9600);
  pinMode(Button_pin, INPUT);
  pinMode(Photodiode_L, INPUT);
  pinMode(Photodiode_R, INPUT);
  for (int i = 12; i <= 15; i++) {  //Motor pins are 12, 13, 14, 15
    ledcSetup(i, 255, 8);           //ledc settings (channel, frequency, bits)
    ledcAttachPin(i, i);            //The motor pin is bound to the corresponding channel
  }
  do {
    Serial.println("Wait for the button to press ");
  }
  while (digitalRead(Button_pin) == 1);
}
void Motor(int L1, int L2 , int R1, int R2) {
  ledcWrite(12, L1);
  ledcWrite(13, L2);
  ledcWrite(14, R1);
  ledcWrite(15, R2);
}
void loop() { 
  int num_L = analogRead(Photodiode_L);
  int num_R = analogRead(Photodiode_R);
  Serial.print("num_L:");
  Serial.println(num_L);
  Serial.print("num_R:");
  Serial.println(num_R);
  if ((num_L - num_R) > 400) {              //The light on the right is strong, turn right
    Motor(0, 100, 100, 0);
  }
  else if ((num_R - num_L) > 400) {         //The light on the left is strong, turn left
    Motor(100, 0, 0, 100);
  }
  else if (num_R < 3000 && num_L < 3000) {  // The light is straight ahead, go forward
    Motor( 0, 100,0, 100);
  }
  else {
    Motor(0, 0, 0, 0);
  }
}
