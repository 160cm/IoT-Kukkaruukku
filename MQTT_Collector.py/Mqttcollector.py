import paho.mqtt.client as mqtt
import MySQLdb
from array import *
kayttaja = "ubuntu"
tunnus = "tvtatk2018"
Kosteusdata = " "
Lampodata = " "
Valodata = " "
db = MySQLdb.connect("localhost","ubuntu","tvtatk2018","testDB")
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("Valo")
    client.subscribe("Kosteus")
    client.subscribe("Lampo")
    client.username_pw_set(kayttaja, tunnus)  
 
def on_message(client, userdata, msg):
    topic = msg.topic
    viesti = msg.payload
    if  topic == "hattu":
     print("vaarin meni")
   
    elif topic == "Lampo":
    global Lampodata
    Lampodata = viesti
    print(Lampodata)
   
    elif topic == "Kosteus":
    global Kosteusdata
    Kosteusdata = viesti
    print(Kosteusdata)
 
    elif topic == "Valo":
    global Valodata
    Valodata = viesti
    print(Valodata)
 
    cursor = db.cursor()
    cursor.execute("""INSERT INTO Sensoriarvot (Lampo,Kosteus,Valo) VALUES (%s, %s, %s)""",(Lampodata,Kosteusdata,Valodata))
    db.commit()
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("192.168.2.108", 1883, 60)
client.loop_forever()