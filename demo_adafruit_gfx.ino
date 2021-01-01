#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <Ticker.h>

Ticker blinker;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ADC_MODE(ADC_VCC)

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

  // Suspected brownout problems as display crashed, ticker continued to run, only display crashed
  // tried 3 graphics libraries, adafruit gfx, SSD1306Wire and U8g2, only U8g2 runs stable on Wifi Kit 8
  blinker.attach(0.2, displayVoltage); //Use attach_ms if you need time in ms
  
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }
}


void loop() {
  display.clearDisplay();
  display.setCursor(10,10);
  display.setTextColor(SSD1306_WHITE);
  display.print("Muahaha!");

  display.display();
  delay(100);

  for (int i = 0; i < 20; ++i) {
    display.drawPixel(random(127), random(31), SSD1306_WHITE);
    display.display();
    delay(30);
  }

  for (int i = 0 ; i < 100; i+=5) {
    display.clearDisplay();
    display.drawBitmap(10+i, 2, earth, 24, 24, 1);
    display.display();
    delay(100);
  }
}

void displayVoltage() {
  Serial.print("Voltage: ");
  Serial.println(ESP.getVcc());
}
