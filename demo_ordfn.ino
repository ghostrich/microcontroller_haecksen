#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <Fonts/FreeSerif9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int hCenter = 64;                      // horizontal center of animation
int vCenter = 16;                      // vertical center of animation
int Hstar, Vstar;                      // star location currently
int Quantity = 100;                    // number of stars
int StarProgress[100];                 // array that tracks progress of each star
int StarAngle[100] = {};               // array that tracks angle of each star
int interval[75] = {};                 // array used to track speed of each star
//int loops = 0;

const unsigned char witch1 [] PROGMEM = {
// 'witch1', 24x24px
0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x0f, 0xf7, 0xf0, 0x1f, 0xf3, 0xf8, 0x3f, 0xe1, 0xfc, 0x3f, 
0xe1, 0xfc, 0x7f, 0x80, 0xfe, 0xff, 0xc1, 0xff, 0x93, 0x80, 0xff, 0xc7, 0x91, 0xff, 0xef, 0xe3, 
0xe7, 0xff, 0x01, 0xcf, 0xfe, 0x00, 0x1f, 0xfc, 0x03, 0x3f, 0xf8, 0x00, 0x7f, 0xfc, 0x81, 0xff, 
0xfb, 0x83, 0xff, 0xf0, 0x07, 0xff, 0x60, 0x0f, 0xfe, 0x38, 0x4f, 0xfc, 0x10, 0xcf, 0xf8, 0x09, 
0x9f, 0xf0, 0x07, 0xff, 0xe0, 0x03, 0xff, 0xc0
};

const unsigned char witch2 [] PROGMEM = {
// 'witch2', 24x24px
0x03, 0xff, 0xc0, 0x07, 0xff, 0xe0, 0x0f, 0xf7, 0xf0, 0x1f, 0xf3, 0xf8, 0x3f, 0xe1, 0xfc, 0x3f, 
0xe1, 0xfc, 0x7f, 0x80, 0xfe, 0xbb, 0xc1, 0xff, 0xd7, 0x80, 0xff, 0xc7, 0x91, 0xff, 0xef, 0xe3, 
0xe7, 0xff, 0x01, 0xcf, 0xfe, 0x00, 0x1f, 0xfc, 0x03, 0x3f, 0xf8, 0x00, 0x7f, 0xfc, 0x81, 0xff, 
0xfb, 0x83, 0xff, 0xf0, 0x07, 0xff, 0x60, 0x0f, 0xfe, 0x38, 0x4f, 0xfc, 0x10, 0xcf, 0xf8, 0x09, 
0x9f, 0xf0, 0x07, 0xff, 0xe0, 0x03, 0xff, 0xc0
};

const unsigned char tinylaptop [] PROGMEM = {
// 'tinylaptop', 24x24px
0x00, 0x70, 0x00, 0x00, 0x4e, 0x00, 0x00, 0x41, 0x80, 0x00, 0x40, 0x70, 0x00, 0x40, 0x0e, 0x00, 
0x40, 0x02, 0x00, 0x41, 0xc2, 0x00, 0x41, 0x02, 0x00, 0x4d, 0x1a, 0x00, 0x51, 0x0a, 0x00, 0x51, 
0x12, 0x00, 0x51, 0x0a, 0x00, 0x61, 0xda, 0x00, 0xf8, 0x02, 0x03, 0xbe, 0x02, 0x0d, 0x57, 0xc2, 
0x3a, 0xab, 0xf2, 0x75, 0x55, 0x7e, 0xfa, 0xaa, 0xbc, 0x3d, 0x55, 0x5c, 0x0e, 0xaa, 0xb8, 0x03, 
0xd5, 0x60, 0x00, 0xea, 0xc0, 0x00, 0x3f, 0x80
};

const unsigned char tiny[] PROGMEM = {
// 'tiny', 1px
0x00
};

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); 
  }

// 'splody stars at the end
    for (int i = 0; i < Quantity; i++) {          // loop to setup initial stars
    StarAngle[i] = random(360);                 // generates random angle for each star
    interval[i] = (random(4))+1;                // generates random speed for each star +1 keeps stars from being zero
  }  
}

void loop() {
// say hi
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSansBold12pt7b);
  display.setCursor(40, 30);
  display.println(F("hi"));
  display.display();
  delay(1000);

// no1
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(40, 20);
  display.println(F("oh."));
  display.display();
  delay(500);

// no2
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(40, 20);
  display.println(F("oh.."));
  display.display();
  delay(500);

// no3
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(40, 20);
  display.println(F("oh..."));
  display.display();
  delay(500);

// go, on...
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(40, 20);
  display.println(F("I mean:"));
  display.display();
  delay(500);

// be polite
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(40, 20);
  display.println(F("hello! :)"));
  display.display();
  delay(500);
  
// alderaan explosion
  Serial.println(F("circle"));
  for (int radius = 0; radius < 60; radius++) {
    display.fillCircle(66, 16, 20, SSD1306_BLACK); 
    display.drawCircle(66, 16, radius, SSD1306_WHITE); 
    display.display();
    delay(30);
  }

//there
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(40, 20);
  display.println(F("there."));
  display.display();
  delay(500);

//clear space
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(1, 20);
  display.println(F("made some space"));
  display.display();
  delay(1000);

  display.clearDisplay();
  display.drawBitmap(1, 1, tiny, 1, 1, 1);
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSansBold12pt7b);
  display.setCursor(25, 20);
  display.println(F("to fly!"));
  display.display();
  delay(1000);

  display.clearDisplay();
  display.drawBitmap(1, 1, tiny, 1, 1, 1);
  display.display();
  delay(1000);

  display.clearDisplay();
  display.drawBitmap(10, 2, witch1, 24, 24, 1);
  display.drawBitmap(100, 2, tinylaptop, 24, 24, 1);
  display.display();
  delay(200);

  display.clearDisplay();
  display.drawBitmap(11, 3, witch2, 24, 24, 1);
  display.drawBitmap(99, 3, tinylaptop, 24, 24, 1);
  display.display();
  delay(200);

  display.clearDisplay();
  display.drawBitmap(12, 4, witch1, 24, 24, 1);
  display.drawBitmap(98, 4, tinylaptop, 24, 24, 1);
  display.display();
  delay(200);

  display.clearDisplay();
  display.drawBitmap(13, 5, witch2, 24, 24, 1);
  display.drawBitmap(97, 5, tinylaptop, 24, 24, 1);
  display.display();
  delay(200);

  display.clearDisplay();
  display.drawBitmap(14, 6, witch1, 24, 24, 1);
  display.drawBitmap(96, 6, tinylaptop, 24, 24, 1);
  display.display();
  delay(100);

  display.clearDisplay();
  display.drawBitmap(15, 7, witch2, 24, 24, 1);
  display.drawBitmap(95, 7, tinylaptop, 24, 24, 1);
  display.display();
  delay(100);

  display.clearDisplay();
  display.drawBitmap(16, 8, witch1, 24, 24, 1);
  display.drawBitmap(94, 8, tinylaptop, 24, 24, 1);
  display.display();
  delay(100);

  display.clearDisplay();
  display.drawBitmap(17, 7, witch2, 24, 24, 1);
  display.drawBitmap(93, 7, tinylaptop, 24, 24, 1);
  display.display();
  delay(90);

  display.clearDisplay();
  display.drawBitmap(18, 6, witch1, 24, 24, 1);
  display.drawBitmap(92, 6, tinylaptop, 24, 24, 1);
  display.display();
  delay(90);

  display.clearDisplay();
  display.drawBitmap(19, 5, witch2, 24, 24, 1);
  display.drawBitmap(91, 5, tinylaptop, 24, 24, 1);
  display.display();
  delay(90);

  display.clearDisplay();
  display.drawBitmap(20, 4, witch1, 24, 24, 1);
  display.drawBitmap(90, 4, tinylaptop, 24, 24, 1);
  display.display();
  delay(90);

  display.clearDisplay();
  display.drawBitmap(21, 3, witch2, 24, 24, 1);
  display.drawBitmap(89, 3, tinylaptop, 24, 24, 1);
  display.display();
  delay(80);

  display.clearDisplay();
  display.drawBitmap(22, 2, witch1, 24, 24, 1);
  display.drawBitmap(88, 2, tinylaptop, 24, 24, 1);
  display.display();
  delay(80);

  display.clearDisplay();
  display.drawBitmap(23, 3, witch2, 24, 24, 1);
  display.drawBitmap(87, 3, tinylaptop, 24, 24, 1);
  display.display();
  delay(80);

  display.clearDisplay();
  display.drawBitmap(24, 4, witch1, 24, 24, 1);
  display.drawBitmap(86, 4, tinylaptop, 24, 24, 1);
  display.display();
  delay(70);

  display.clearDisplay();
  display.drawBitmap(25, 5, witch2, 24, 24, 1);
  display.drawBitmap(85, 5, tinylaptop, 24, 24, 1);
  display.display();
  delay(70);

  display.clearDisplay();
  display.drawBitmap(26, 6, witch1, 24, 24, 1);
  display.drawBitmap(84, 6, tinylaptop, 24, 24, 1);
  display.display();
  delay(60);

  display.clearDisplay();
  display.drawBitmap(27, 7, witch2, 24, 24, 1);
  display.drawBitmap(83, 7, tinylaptop, 24, 24, 1);
  display.display();
  delay(60);

  display.clearDisplay();
  display.drawBitmap(28, 8, witch1, 24, 24, 1);
  display.drawBitmap(82, 8, tinylaptop, 24, 24, 1);
  display.display();
  delay(60);

  display.clearDisplay();
  display.drawBitmap(29, 7, witch2, 24, 24, 1);
  display.drawBitmap(81, 7, tinylaptop, 24, 24, 1);
  display.display();
  delay(60);

  display.clearDisplay();
  display.drawBitmap(30, 6, witch1, 24, 24, 1);
  display.drawBitmap(80, 6, tinylaptop, 24, 24, 1);
  display.display();
  delay(50);

  display.clearDisplay();
  display.drawBitmap(31, 5, witch2, 24, 24, 1);
  display.drawBitmap(79, 5, tinylaptop, 24, 24, 1);
  display.display();
  delay(50);

  display.clearDisplay();
  display.drawBitmap(32, 4, witch2, 24, 24, 1);
  display.drawBitmap(78, 4, tinylaptop, 24, 24, 1);
  display.display();
  delay(50);

  display.clearDisplay();
  display.drawBitmap(33, 3, witch2, 24, 24, 1);
  display.drawBitmap(77, 3, tinylaptop, 24, 24, 1);
  display.display();
  delay(50);

  display.clearDisplay();
  display.drawBitmap(34, 2, witch2, 24, 24, 1);
  display.drawBitmap(76, 2, tinylaptop, 24, 24, 1);
  display.display();
  delay(40);

  display.clearDisplay();
  display.drawBitmap(35, 3, witch2, 24, 24, 1);
  display.drawBitmap(75, 3, tinylaptop, 24, 24, 1);
  display.display();
  delay(40);
  
  display.clearDisplay();
  display.drawBitmap(36, 4, witch2, 24, 24, 1);
  display.drawBitmap(74, 4, tinylaptop, 24, 24, 1);
  display.display();
  delay(40);

  display.clearDisplay();
  display.drawBitmap(37, 5, witch2, 24, 24, 1);
  display.drawBitmap(73, 5, tinylaptop, 24, 24, 1);
  display.display();
  delay(40);

  display.clearDisplay();
  display.drawBitmap(38, 6, witch2, 24, 24, 1);
  display.drawBitmap(72, 6, tinylaptop, 24, 24, 1);
  display.display();
  delay(30);

  display.clearDisplay();
  display.drawBitmap(39, 7, witch2, 24, 24, 1);
  display.drawBitmap(71, 7, tinylaptop, 24, 24, 1);
  display.display();
  delay(20);

  display.clearDisplay();
  display.drawBitmap(40, 8, witch2, 24, 24, 1);
  display.drawBitmap(70, 8, tinylaptop, 24, 24, 1);
  display.display();
  delay(10);

// 'splody stars solid
  for (int loops = 0; loops < 40; loops++) {
    unsigned long currentMillis = millis();
    display.clearDisplay();                       // clear display
    for (int i = 4; i < Quantity; i++) {          // loop to draw each star

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
  display.drawBitmap(1, 1, tiny, 1, 1, 1);
  display.display();
  delay(1000);

  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(5, 20);
  display.println(F("come fly too!"));
  display.display();
  delay(1000);

  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setFont(&FreeSerif9pt7b);
  display.setCursor(0, 20);
  display.println(F("happy haecksing!"));
  display.display();
  delay(10000);

}
