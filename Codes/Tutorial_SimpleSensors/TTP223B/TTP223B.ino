  /*
  TTP223B-Capacitive-Touch-Switch-Module
  made on 08 Nov 2020
  by Amir Mohammad Shojaee @ Electropeak
  Home

*/
const int SENSOR_PIN = 2; 
         
void setup() {
  Serial.begin(9600);
  // initialize the Arduino's pin as aninput
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  if(digitalRead(SENSOR_PIN) == HIGH){
    Serial.println("Sensor is touched");
    while(digitalRead(SENSOR_PIN) == HIGH){}
  }
}
