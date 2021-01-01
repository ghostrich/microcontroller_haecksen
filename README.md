# microcontroller_haecksen

Setup:
- install Arduino suite -> https://www.arduino.cc/en/software
- install ESP8266:
https://arduino-esp8266.readthedocs.io/en/latest/installing.html
- install libraries:
U8G2 <br>
Adafruit GFX Library<br>
Adafruit SSD1306<br>
- upload .ino files from this repository


rc3_intro.ino

<img src="rc3.jpg" width=400/>

Images are black and white and can have these dimensions: 128x32 

Here is a tool to convert images to .xbm (needed for U8G2):
https://www.freefileconvert.com/

Here is a tool to convert images to "Adafruit GFXbitmapFont":<br>
http://javl.github.io/image2cpp/


<br>mqtt example</br>

Add your WiFi SSID and password and a MQTT server (e.g. test.mosquitto.org)

For the Python script (to be run on your computer):
Install https://pypi.org/project/paho-mqtt/

More info on mqtt: 
https://medium.com/python-point/mqtt-basics-with-python-examples-7c758e605d4
