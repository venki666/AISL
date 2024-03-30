#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "s-VmlHvgBrXLeJ_L60UFvufKL4B8FWfG";
 
float x,y,z;
float lat, lon;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "my_home";
char pass[] = "myhome123!";

WidgetTerminal terminal(V2);

BLYNK_WRITE(V1) {
  //acceleration force applied to axis x
   x = param[0].asFloat(); 
  //acceleration force applied to axis y
   y = param[1].asFloat();
  //acceleration force applied to axis y
   z = param[2].asFloat();
}

BLYNK_WRITE(V0) {
  //GPS Latitude
   lat = param[0].asFloat(); 
  //GPS Longitude
   lon = param[1].asFloat();
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{

  Blynk.run();


  Serial.print("Latitude and Longitude:: ");
  Serial.print(lat);
  Serial.print(" ");
  Serial.println(lon);

  
  terminal.print("Accelerometer readings:: ");
  terminal.print(x);
  terminal.print(" ");
  terminal.print(y);
  terminal.print(" ");
  terminal.println(z);

  delay(200);
}
