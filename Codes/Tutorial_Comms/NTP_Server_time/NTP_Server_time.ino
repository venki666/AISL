#include <WiFi.h>
#include "time.h"

//const char* ssid       = "";
//const char* password   = "";

const char* ssid     = "Caffeine";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "abc12345";     // The password of the Wi-Fi network


const char* ntpServer = "2.kr.pool.ntp.org";
const long  gmtOffset_sec = +32400;
const int   daylightOffset_sec = 0;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
 // WiFi.disconnect(true);
 // WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(1000);
  printLocalTime();
}
