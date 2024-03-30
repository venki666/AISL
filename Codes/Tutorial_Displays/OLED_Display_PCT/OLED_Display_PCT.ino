
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PCT2075.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET     4 //Not USE in the DEMO

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_PCT2075 PCT2075;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
   PCT2075 = Adafruit_PCT2075();
 if (!PCT2075.begin()) {
    Serial.println("Couldn't find PCT2075 chip");
    while (1);
  }
  
  Serial.println("Found PCT2075 chip");



}

void loop() {

  //showing on display
  display.clearDisplay();
  display.setCursor(0,0); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  display.println(F("Temperature:"));
  display.println(PCT2075.getTemperature());
  display.display();
  delay(1000);
}
