#include <U8g2lib.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C display(U8G2_R0, /* reset=*/ 16, /* clock=*/ 5, /* data=*/ 4);

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
  0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x80, 0x81, 0xBF, 0xBF, 0xBF, 
  0x81, 0xA1, 0x81, 0xB1, 0x81, 0xA1, 0x01, 0xB0, 0x81, 0xBF, 0x01, 0xBF, 
  0x81, 0x9F, 0x01, 0xA0, 0x81, 0x99, 0x81, 0xB1, 0x81, 0xB1, 0xBF, 0xBF, 
  0x01, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF
};

const unsigned char rocket [] PROGMEM = {
  // 'brandy_rockets_2, 14x32px
  0xC0, 0x00, 0xE0, 0x01, 0xF8, 0x03, 0xFC, 0x0F, 0xFC, 0x0F, 0x1E, 0x1E, 
  0x0E, 0x1C, 0x07, 0x38, 0x07, 0x38, 0x0F, 0x3C, 0x1F, 0x3E, 0x3F, 0x3F, 
  0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 0xFF, 0x3F, 
  0xFE, 0x1F, 0xFE, 0x0F, 0xF2, 0x0F, 0xE2, 0x0B, 0xE3, 0x19, 0xE1, 0x11, 
  0xE1, 0x11, 0xC1, 0x10, 0xC1, 0x10, 0xC1, 0x18, 0xC3, 0x18, 0xC2, 0x08, 
  0xC0, 0x00, 0xC0, 0x00
};

void setup() {
  Serial.begin(115200);
  display.begin();


  for (int i = 0; i < Quantity; i++) {          // loop to setup initial stars
    StarAngle[i] = random(360);                 // generates random angle for each star
    interval[i] = (random(4))+1;                // generates random speed for each star +1 keeps stars from being zero
  }  

  display.setFont(u8g2_font_helvB12_tf);//u8g2_font_unifont_t_latin);

}

void loop() {
  display.clearBuffer();
  display.drawXBMP(-24, 0, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);
    
  display.clearBuffer();
  display.drawXBMP(-12, 0, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);
  
  display.clearBuffer();  
  display.drawXBMP(0, 0, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);
  
  display.clearBuffer();
  display.drawXBMP(12, 0, 32, 32, rc3logo);
  display.sendBuffer();  
  delay(100);
  
  display.clearBuffer();
  display.drawXBMP(24, 0, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);
  
  display.clearBuffer();
  display.drawXBMP(36, 0, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);
  
  display.clearBuffer();
  display.drawXBMP(48, 0, 32, 32, rc3logo);
  display.sendBuffer();
  delay(1000);
  
  display.clearBuffer();
  display.drawXBMP(48, -12, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);

  display.clearBuffer();
  display.drawXBMP(48, -24, 32, 32, rc3logo);
  display.sendBuffer();
  delay(100);

  display.clearBuffer();
  display.drawXBMP(48, -36, 32, 32, rc3logo);
  display.sendBuffer();
  delay(1000);

  
  
  display.drawUTF8(15, 20, "haecksen.org");
  display.sendBuffer();
  delay(3000);

  display.clearBuffer();
  display.drawXBMP(57, 0, 14, 32, rocket);
  display.sendBuffer();
  delay(100);

  display.clearBuffer();
  display.drawXBMP(57, -6, 14, 32, rocket);
  display.sendBuffer();
  delay(100);  

  display.clearBuffer();
  display.drawXBMP(57, -12, 14, 32, rocket);
  display.sendBuffer();
  delay(100);   

  display.clearBuffer();
  display.drawXBMP(57, -18, 14, 32, rocket);
  display.sendBuffer();
  delay(100);  

  display.clearBuffer();
  display.drawXBMP(57, -24, 14, 32, rocket);
  display.sendBuffer();
  delay(100); 

  display.clearBuffer();
  display.drawXBMP(57, -30, 14, 32, rocket);
  display.sendBuffer();
  delay(100);

  display.clearBuffer();
  display.drawXBMP(57, -36, 14, 32, rocket);
  display.sendBuffer();
  delay(100);

  for (int loops = 0; loops < 50; loops++) {
    unsigned long currentMillis = millis();
    display.clearBuffer();                       // clear display
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
        display.drawPixel(Hstar, Vstar);
      }
    }
    display.sendBuffer(); 
    delay(100);
    Serial.println(loops);
  }
  display.clearBuffer();  
  display.sendBuffer();

  display.drawUTF8(30, 20, "have fun!");
  display.sendBuffer();
}
