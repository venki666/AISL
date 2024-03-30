/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPL7pGAneZb"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "xBZ0xdHUBkuWyyqNkgHd_E466D8j1oap"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include "Adafruit_APDS9960.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

Adafruit_APDS9960 apds;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wangd6";
char pass[] = "wdx251006";

BlynkTimer timer;


// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  uint16_t r, g, b, c;
  apds.getColorData(&r, &g, &b, &c);
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  
  Blynk.virtualWrite(V2, millis() / 1000);
  Blynk.virtualWrite(V0, c);
}

void setup()
{
  // Debug console
  Serial.begin(115200);
  if(!apds.begin())Serial.println("failed to initialize device! Please check your wiring.");
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
  //set iintegration time
  uint16_t temp1 = 176;
  apds.setADCIntegrationTime(temp1);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
