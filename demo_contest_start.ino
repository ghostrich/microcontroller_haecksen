#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char earth [] PROGMEM = {
// 'earth', 24x24px
0x03, 0xff, 0x80, 0x0c, 0x00, 0x70, 0x0c, 0x00, 0x70, 0x14, 0x00, 0x48, 0x63, 0xc0, 0x44, 0x60, 
0x3f, 0x84, 0x40, 0x3f, 0x8e, 0x80, 0x00, 0x0a, 0xe1, 0xfe, 0x0a, 0x92, 0x01, 0x06, 0x92, 0x00, 
0x82, 0x92, 0x00, 0x82, 0x92, 0x00, 0x82, 0x91, 0xc0, 0x82, 0x90, 0x20, 0x82, 0xe0, 0x21, 0x02, 
0x80, 0x21, 0x02, 0x80, 0x21, 0x02, 0x60, 0x22, 0x04, 0x60, 0x1c, 0x04, 0x10, 0x00, 0x08, 0x0c, 
0x00, 0x70, 0x0c, 0x00, 0x70, 0x03, 0xff, 0x80
};

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
}

void loop() {
  Serial.println(F("pixels"));
  for (int numberofpixels = 0; numberofpixels < 25; numberofpixels++) {
    display.clearDisplay();
    display.display();
    display.clearDisplay(); 
    display.drawPixel(numberofpixels, numberofpixels, SSD1306_WHITE);
    display.display();
    delay(10);
  }
  
  Serial.println(F("circle"));
  for (int radius = 0; radius < 25; radius++) {
    display.clearDisplay();
    display.display();
    display.clearDisplay();
    display.drawCircle(10, 10, radius, SSD1306_WHITE); 
    display.display();
    delay(10);
  }
  Serial.println(F("rect"));
  for (int wh = 0; wh < 50; wh++) {
    display.clearDisplay();
    display.display();
    display.clearDisplay();
    display.drawRect(50,5,wh,wh,SSD1306_WHITE); 
    display.display();
    delay(10);
  }
  Serial.println(F("round rect"));
  for (int wh = 0; wh < 40; wh++) {
    display.clearDisplay();
    display.display();
    display.clearDisplay();
    display.drawRoundRect(100, 10, wh, wh, 4, SSD1306_WHITE);
    display.display();
    delay(10);
  }


  display.clearDisplay();
  display.drawBitmap(10, 2, earth, 24, 24, 1);
  display.display();
  delay(3000);
    
}
