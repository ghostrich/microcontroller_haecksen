#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "WIFI SSID";
const char* password =  "WIFI password"
const char* mqttServer = "Server Adresse";

const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

WiFiClient espClient;
PubSubClient client(espClient);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("WiFi-Verbindung..");
  }
  Serial.println("Mit WiFi verbunden");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  connectMQTT();
 

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
}

void connectMQTT() {
    while (!client.connected()) {
      Serial.println("Verbinde zu MQTT...");
 
      if (client.connect("")) {
        client.subscribe("haecksen");
        Serial.println("verbunden");  
      } else {
        Serial.print("fehlgeschlagen: ");
        Serial.print(client.state());
        delay(2000);
    }
  }
}

void drawText(String message) {
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0); 
  display.print(message);
  display.display();
  delay(3000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Nachricht angekommen für Thema: ");
  Serial.println(topic);
  String recv_payload = String(( char *) payload);
 
  Serial.print("Nachricht: ");
  Serial.println((char *)payload);
  drawText((char *)payload);
}

 
void loop() {
  connectMQTT();
  client.loop();
  delay(100);
}
