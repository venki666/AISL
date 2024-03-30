#define LED_BUILT_IN 33 
 
void setup() {
  pinMode(LED_BUILT_IN, OUTPUT); // Set the pin as output
}
 
// Remember that the pin work with inverted logic
// LOW to Turn on and HIGH to turn off
void loop() {
  digitalWrite(LED_BUILT_IN, LOW); //Turn on
  delay (1000); //Wait 1 sec
  digitalWrite(LED_BUILT_IN, HIGH); //Turn off
  delay (1000); //Wait 1 sec
}
