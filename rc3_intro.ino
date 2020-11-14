#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int hCenter = 64;                      // horizontal center of animation
int vCenter = 16;                      // vertical center of animation
int Hstar, Vstar;                      // star location currently
int Quantity = 100;                    // number of stars
int StarProgress[100];                 // array that tracks progress of each star
int StarAngle[100] = {};               // array that tracks angle of each star
int interval[75] = {};                 // array used to track speed of each star
//int loops = 0;

const unsigned char rc3logo [] PROGMEM = {
  // rc3logo, 32x32px
  0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 
  0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x01, 0x81, 0xfd, 0xfd, 0xfd, 
  0x81, 0x85, 0x81, 0x8d, 0x81, 0x85, 0x80, 0x0d, 0x81, 0xfd, 0x80, 0xfd, 0x81, 0xf9, 0x80, 0x05, 
  0x81, 0x99, 0x81, 0x8d, 0x81, 0x8d, 0xfd, 0xfd, 0x80, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff
};

const unsigned char rocket [] PROGMEM = {
  // 'brandy_rockets_2, 14x32px
  0x03, 0x00, 0x07, 0x80, 0x1f, 0xc0, 0x3f, 0xf0, 0x3f, 0xf0, 0x78, 0x78, 0x70, 0x38, 0xe0, 0x1c, 
  0xe0, 0x1c, 0xf0, 0x3c, 0xf8, 0x7c, 0xfc, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 0xff, 0xfc, 
  0xff, 0xfc, 0xff, 0xfc, 0x7f, 0xf8, 0x7f, 0xf0, 0x4f, 0xf0, 0x47, 0xd0, 0xc7, 0x98, 0x87, 0x88, 
  0x87, 0x88, 0x83, 0x08, 0x83, 0x08, 0x83, 0x18, 0xc3, 0x18, 0x43, 0x10, 0x03, 0x00, 0x03, 0x00
};

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

  for (int i = 0; i < Quantity; i++) {          // loop to setup initial stars
    StarAngle[i] = random(360);                 // generates random angle for each star
    interval[i] = (random(4))+1;                // generates random speed for each star +1 keeps stars from being zero
  }  

  
  display.clearDisplay();
  display.display();
  display.clearDisplay();
  display.drawBitmap(-24, 0, rc3logo, 32, 32, 1);
  display.display();
  delay(100);
    
  display.clearDisplay();
  display.drawBitmap(-12, 0, rc3logo, 32, 32, 1);
  display.display();
  delay(100);
  
  display.clearDisplay();  
  display.drawBitmap(0, 0, rc3logo, 32, 32, 1);
  display.display();
  delay(100);
  
  display.clearDisplay();
  display.drawBitmap(12, 0, rc3logo, 32, 32, 1);
  display.display();  
  delay(100);
  
  display.clearDisplay();
  display.drawBitmap(24, 0, rc3logo, 32, 32, 1);
  display.display();
  delay(100);
  
  display.clearDisplay();
  display.drawBitmap(36, 0, rc3logo, 32, 32, 1);
  display.display();
  delay(100);
  
  display.clearDisplay();
  display.drawBitmap(48, 0, rc3logo, 32, 32, 1);
  display.display();
  delay(1000);
  
  display.clearDisplay();
  display.drawBitmap(48, -12, rc3logo, 32, 32, 1);
  display.display();
  delay(100);

  display.clearDisplay();
  display.drawBitmap(48, -24, rc3logo, 32, 32, 1);
  display.display();
  delay(100);

  display.clearDisplay();
  display.drawBitmap(48, -36, rc3logo, 32, 32, 1);
  display.display();
  delay(1000);
  
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 10);
  display.println(F("haecksen"));
  display.display();
  delay(3000);

  display.clearDisplay();
  display.drawBitmap(57, 0, rocket, 14, 32, 1);
  display.display();
  delay(3000);

  for (int loops = 0; loops < 50; loops++) {
    unsigned long currentMillis = millis();
    display.clearDisplay();                       // clear display
    for (int i = 0; i < Quantity; i++) {          // loop to draw each star

      if (StarProgress[i] > 70) {                // if statement to reset stars after going off screen
        StarProgress[i] = StarProgress[i] - 70;  // resets star progress
        StarAngle[i] = random(360);               // resets star angle
        interval[i] = (random(4))+1;              // resets star speed    
      }else{
        StarProgress[i] = StarProgress[i] + interval[i];                            // distance traveled for star
      }
    
      if (currentMillis - StarProgress[i] >= interval[i] && StarProgress[i] > 0) {  // if statement to exclude some star paths
        Hstar = (hCenter + (sin(StarAngle[i] / 57.296) * StarProgress[i] ));        // calculates star horizontal coordinate
        Vstar = (vCenter + (cos(StarAngle[i] / 57.296) * StarProgress[i] ));        // calculates star horizontal coordinate
        display.drawPixel(Hstar, Vstar, SSD1306_WHITE);
      }
    }
    display.display(); 
    delay(100);
    Serial.println(loops);
  }
  display.clearDisplay();  
  display.display();

  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 10);
  display.println(F("have fun!"));
  display.display();
}

void loop() {

}
