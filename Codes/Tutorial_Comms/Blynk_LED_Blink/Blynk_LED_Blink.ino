#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9FwAEpdTY3-k4B_Xv25Z3YcFunj5iz4j";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "my_home";
char pass[] = "myhome123!";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
