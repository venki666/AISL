int QTI_Max, QTI_L = 39, QTI_R = 36, Button_pin = 18;
int Speed = 160;
void setup() {
  Serial.begin(9600);
  pinMode(QTI_L, INPUT);
  pinMode(QTI_R, INPUT);
  pinMode(Button_pin, INPUT);
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

void loop() {
  QTI_Max = digitalRead(QTI_L) * 2 + digitalRead(QTI_R); // black line returns 1
  Serial.println( QTI_Max);
  delay(5);
  switch (QTI_Max) {
    case 0:
      Motor(Speed, 0, Speed, 0); // backward
      break;
    case 1:
      Motor(0, Speed, 0, Speed / 2); // turn right
      break;
    case 2:
      Motor(0, Speed / 2, 0, Speed); // turn left
      break;
    case 3:
      Motor(0, Speed + 40, 0, Speed + 40); // forward
      break;
  }
}
