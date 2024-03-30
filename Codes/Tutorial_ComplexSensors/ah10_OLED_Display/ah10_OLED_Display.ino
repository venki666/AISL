
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHT10.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define OLED_RESET     4 //Not USE in the DEMO

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_AHT10 aht;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  if (! aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 found");


}

void loop() {

  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  //range of c is from 0 to 65535
  //a 16 bits value 
  //showing on display
  display.clearDisplay();
  display.setCursor(0,0); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("TEMP: "));
  display.println(temp.temperature);
  display.setCursor(0,15); 
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.println(F("HUM:"));
  display.println(humidity.relative_humidity);
  display.display();
}
