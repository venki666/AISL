#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5
#define NUMPIXELS  1
#define DELAYVAL 250 // Time (in milliseconds) to pause between pixels

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();
  
  delay(DELAYVAL); // Pause
  
  pixels.setPixelColor(0, pixels.Color(0, 0, 150));
  pixels.show();

  delay(DELAYVAL); // Pause

  pixels.setPixelColor(0, pixels.Color(150, 0, 150));
  pixels.show();

  delay(DELAYVAL); // Pause
}
