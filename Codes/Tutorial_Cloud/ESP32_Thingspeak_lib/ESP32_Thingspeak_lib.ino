#include <WiFi.h> 
WiFiClient WIFI_CLIENT;
#include <ThingSpeak.h>

const char* ssid     = "Caffeine";
const char* password = "abc12345";

unsigned long Channel_ID = 746330;
const char * WriteAPIKey = "";
unsigned long tiempo_actual = 0;

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(WIFI_CLIENT);

  Serial.println();
  Serial.print("Connecting with ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("WiFi conected. IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if((millis()-time_actual)>= 16000){ // Each 16 seconds upload.
          int randomnum = random(0,90);
          time_actual = millis();
          // Send random number to field1.
          int x = ThingSpeak.writeField(Channel_ID, 1, randomnum, WriteAPIKey);
          if(x == 200){ Serial.println("Upload correct: " + String(randomnum));}
          else{ Serial.println("Upload failed: " + String(randomnum)); }
  }
}