import paho.mqtt.client as mqtt 
from random import randrange, uniform
import time
import numpy as np

mqttBroker ="test.mosquitto.org" 

client = mqtt.Client("HaecksenFahrplan")
client.connect(mqttBroker)


events = np.array(['18:00-20:00 // Spy-Apps und die APT-Luecke // Mighty Mary //Leena',
                   '19:00-21:00 // Microcontroller // Sparkling Silvia // ghostrich  ',
                   'Anderes Zeug in Raum YYY mit grossartiger Haeckse                '])




while True:
    for x in range(len(events)):
        message = events[x]
        client.publish("haecksen_fahrplan", None,0,True);
        client.publish("haecksen_fahrplan", message)
        print("Just published " + message + " to topic haecksen_fahrplan")
        time.sleep(10)
