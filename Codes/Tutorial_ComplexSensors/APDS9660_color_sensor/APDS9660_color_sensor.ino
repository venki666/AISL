#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include <Adafruit_NeoPixel.h>

Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
Adafruit_NeoPixel pixels1(1, 5, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  if (tsl.begin()) 
  {
    Serial.println(F("Found a TSL2591 sensor"));
  } 
  else 
  {
    Serial.println(F("No sensor found ... check your wiring?"));
    while (1);
  }
  sensor_t sensor;
  tsl.getSensor(&sensor);
  tsl.setGain(TSL2591_GAIN_MED);      // 25x gain
  tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);

}

void loop() {
  
  uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);
  uint16_t c = 255 - (((float)x/65535) * 255*4);

  //showing the color through neopixial
 // for(int i=0; i<3; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    pixels1.setPixelColor(0, pixels1.Color(c, c, c));

    pixels1.show();   // Send the updated pixel colors to the hardware.

    delay(10); // Pause before next pass through loop

    // wait a bit before reading again
 // }
 // delay(1000);
}
