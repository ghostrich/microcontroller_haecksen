#include <SPI.h>
#include <Wire.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

Ticker ticker;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);
ADC_MODE(ADC_VCC)

const unsigned char bike [] PROGMEM = {
  // 'bike', 13x13px
  0x00, 0x00, 0x66, 0x00, 0x3c, 0x08, 0x10, 0x0f, 0x10, 0x02, 0xf8, 0x03,
  0x0c, 0x06, 0x1e, 0x0f, 0xb3, 0x19, 0xa1, 0x10, 0xb3, 0x19, 0x1e, 0x0f,
  0x0c, 0x06
};

void setup() {
  Serial.begin(115200);

  // Suspected brownout problems as display crashed, ticker continued to run, only display crashed
  // tried 3 graphics libraries, adafruit gfx, SSD1306Wire and U8g2, only U8g2 runs stable on Wifi Kit 8
  ticker.attach(0.2, logVoltage); //Use attach_ms if you need time in ms

  display.begin();
  display.setFont(u8g2_font_ncenB14_tr);
}


void loop() {
  display.clearBuffer();
  
  display.drawUTF8(15,15,"Muahaha!"); // Lower left corner
  display.sendBuffer();
  delay(100);

  for (int i = 0; i < 20; ++i) {
    display.drawPixel(random(127), random(31));
    display.sendBuffer();
    delay(30);
  }

  for (int i = 0 ; i < 100; i+=5) {
    display.clearBuffer();
    display.drawXBMP(127-i, 2, 13, 13, bike); // Upper left corner
    display.sendBuffer();
    delay(100);
  }
}

void logVoltage() {
  Serial.print("Voltage: ");
  Serial.println(ESP.getVcc());
}
