
#define AIN1 16
#define AIN2 17


void setup() {
  Serial.begin(9600);
  
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
}
 
void loop() {
  
  digitalWrite(AIN1,HIGH); 
  digitalWrite(AIN2,LOW);
  delay(5000);
  
  digitalWrite(AIN1,LOW); 
  digitalWrite(AIN2,LOW);  
  delay(1000);
  
  digitalWrite(AIN1,LOW); 
  digitalWrite(AIN2,HIGH);
  delay(5000);
  
  digitalWrite(AIN1,LOW); 
  digitalWrite(AIN2,LOW);
  delay(1000);
   
}
