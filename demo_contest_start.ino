#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);

const unsigned char bike [] PROGMEM = {
  // 'bike', 13x13px
  0x00, 0x00, 0x66, 0x00, 0x3c, 0x08, 0x10, 0x0f, 0x10, 0x02, 0xf8, 0x03,
  0x0c, 0x06, 0x1e, 0x0f, 0xb3, 0x19, 0xa1, 0x10, 0xb3, 0x19, 0x1e, 0x0f,
  0x0c, 0x06
};

void setup() {
  Serial.begin(115200);
  display.begin();
}

void loop() {
  Serial.println(F("pixels"));
  for (int numberofpixels = 0; numberofpixels < 25; numberofpixels++) {
    display.clearDisplay(); 
    display.drawPixel(numberofpixels, numberofpixels);
    display.sendBuffer();
    delay(10);
  }
  
  Serial.println(F("circle"));
  for (int radius = 0; radius < 25; radius++) {
    display.clearDisplay();
    display.drawCircle(10, 10, radius); 
    display.sendBuffer();
    delay(10);
  }
  Serial.println(F("rect"));
  for (int wh = 0; wh < 50; wh++) {
    display.clearDisplay();
    display.drawFrame(50,5,wh,wh); 
    display.sendBuffer();
    delay(10);
  }
  Serial.println(F("round rect"));
  for (int wh = 8; wh < 40; wh++) {
    display.clearDisplay();
    display.drawRFrame(100, 10, wh, wh, 4);
    display.sendBuffer();
    delay(10);
  }


  display.clearDisplay();
  display.drawXBMP(0, 0, 13, 13, bike);
  display.sendBuffer();
  delay(3000);
    
}
