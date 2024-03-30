//This demo shows how to use simple ble with dabble terminal module and
//receving the character from the terminal and lighting up the built-in led

#include <DabbleESP32.h>
#include <Adafruit_NeoPixel.h>
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        5 // On Trinket or Gemma, suggest changing this to 1
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int incoming;

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  Serial.begin(115200); 
  Dabble.begin("MyEsp32-77");       //set bluetooth name of your device
  Serial.println("Bluetooth Device is Ready to Pair");
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  Dabble.processInput();
  if (Terminal.available()) {
    incoming = Terminal.read();
   if(incoming == 49){ //49 is 1 in ASCII 
    // turn on Green
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
     } else if (incoming == 50){ // 50 is 2 in ascii
       pixels.setPixelColor(0, pixels.Color(0, 0, 150));    
     } else if (incoming == 51){
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));  
     } else if (incoming == 48){
      pixels.setPixelColor(0, pixels.Color(0, 0, 0)); 
     } else {
      pixels.setPixelColor(0, pixels.Color(164, 132, 142)); 
     }
    Serial.println(incoming);
    pixels.show();
  }
  delay(20);
}
