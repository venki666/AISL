// Import nessesary libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_HTS221.h>
#include <Adafruit_Sensor.h>
// Set our wifi name and password
const char* ssid = "Caffeine";
const char* password = "abc12345";

// Your thingspeak channel url with api_key query
String serverName = "https://api.thingspeak.com/update?api_key=MOL7GXDGG8LL4RCG";

// Assign some variables to allow us read and send data every minute
unsigned long lastTime = 0;
unsigned long timerDelay = 60000;

Adafruit_HTS221 hts;
void setup() {
  Serial.begin(9600); // Opens up the serial port with a baudrate of 9600 bits per second
  // Try to initialize!
  if (!hts.begin_I2C()) {
    Serial.println("Failed to find HTS221 chip");
    while (1) { delay(10); }
  }
  Serial.println("HTS221 Found!");

  hts.setDataRate(HTS221_RATE_1_HZ);

  WiFi.begin(ssid, password); // Attempt to connect to wifi with our password
  Serial.println("Connecting"); // Print our status to the serial monitor
  // Wait for wifi to connect
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  sensors_event_t temp;
  sensors_event_t humidity;
  hts.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  
  if ((millis() - lastTime) > timerDelay) { // Check if its been a minute
    if(WiFi.status()== WL_CONNECTED){ // Check to make sure wifi is still connected
      sendData(temp.temperature, humidity.relative_humidity); // Call the sendData function defined below
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}


void sendData(double temp, double hum){
  HTTPClient http; // Initialize our HTTP client


  String url = serverName + "&field1=" + temp + "&field2=" + hum; // Define our entire url
      
  http.begin(url.c_str()); // Initialize our HTTP request
      
  int httpResponseCode = http.GET(); // Send HTTP request
      
  if (httpResponseCode > 0){ // Check for good HTTP status code
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
