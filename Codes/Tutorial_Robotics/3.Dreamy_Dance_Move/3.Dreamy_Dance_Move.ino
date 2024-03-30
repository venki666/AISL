 int Button_pin = 18;
 int Speed = 255;                           // Motor PWM setting, that is, the speed can be set in the range of 0-255
void setup()
{
  for (int i = 12; i <= 15; i++) {         //Motor pins are 12, 13, 14, 15
    ledcSetup(i, 5000, 8);                 //ledc settings (channel, frequency, bits)
    ledcAttachPin(i, i);                   //The motor pin is bound to the corresponding channel
  }
  while (digitalRead(Button_pin) == 1);
}
void Motor(int L1, int L2 , int R1, int R2) {   //Custom motor control function
  ledcWrite(12, L1);                            //Channel 12 writes the PWM value
  ledcWrite(13, L2);
  ledcWrite(14, R1);
  ledcWrite(15, R2);
}
void loop()
{
  Motor(0, Speed, 0,Speed);    //Forward   
  delay(500);
   Motor(Speed,0, Speed, 0);   //Backward
  delay(500);
  Motor(Speed, 0,0, Speed);    //Turn Left
  delay(500);
   Motor(0, Speed,Speed, 0 );   //Turn Right
  delay(500);
}
