
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_APDS9960.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET     4 //Not USE in the DEMO

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_APDS9960 apds;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");

  //enable color sensign mode
  apds.enableColor(true);
  //set iintegration time
  uint16_t temp1 = 176;
  apds.setADCIntegrationTime(temp1);
}

void loop() {
  uint16_t r, g, b, c;
  while(!apds.colorDataReady()){
    delay(10);
  }
  apds.getColorData(&r, &g, &b, &c);
  //range of c is from 0 to 65535
  //a 16 bits value 
  //showing on display
  display.clearDisplay();
  display.setCursor(0,0); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("LUX:"));
  display.println(c);
  display.setCursor(0,15); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("RED:"));
  display.println(r);
  display.setCursor(0,30); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("Green:"));
  display.println(g);
  display.setCursor(0,45); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("Blue:"));
  display.println(b);
  display.display();
}
