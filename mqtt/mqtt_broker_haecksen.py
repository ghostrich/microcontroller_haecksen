import paho.mqtt.client as mqtt
import time

mqttBroker ="Server Adresse"

client = mqtt.Client("Haeckse")
client.connect(mqttBroker)

while True:
    topic = "haecksen"
    message = "Lasst uns Dinge tun!"
    client.publish(topic, message)
    print("Published: " + message + " to topic " + topic)
    time.sleep(1)