#include <WiFi.h>
#include <HTTPClient.h>
 
//const char* ssid = "";
//const char* password =  "";

const char* ssid     = "Caffeine";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "abc12345";     // The password of the Wi-Fi network


const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=Gwangju,KR&units=metric&APPID=";
const String key = "cf8cc8a85b876bdbde3d76493122d6d8";
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
 
    HTTPClient http;
 
    http.begin(endpoint + key); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
 
  delay(30000);
 
}
