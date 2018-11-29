#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "TTLab"
#define WLAN_PASS       "a4fg72jk99l1mn"

#define AIO_SERVER      "192.168.2.108"

#define AIO_SERVERPORT  1883

#define BLUE_LED 2
#define RED_LED 0



#define AIO_USERNAME    "ubuntu"
#define AIO_KEY         "tvtatk2018"


// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);


// Setup a feeds called 'red' and 'blue'
Adafruit_MQTT_Subscribe red = Adafruit_MQTT_Subscribe(&mqtt, "red");
Adafruit_MQTT_Subscribe blue = Adafruit_MQTT_Subscribe(&mqtt, "blue");


//Adafruit_MQTT_Publish sendPub = Adafruit_MQTT_Publish(&mqtt, "ledit");
//Adafruit_MQTT_Publish sendPub = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "ledit");
Adafruit_MQTT_Publish sendPub = Adafruit_MQTT_Publish(&mqtt, "ledit");

uint8_t setRed[] = "10";
uint8_t setBlue[] = "20";
uint8_t clearRed[] = "30";
uint8_t clearBlue[] = "40";

/*************************** Sketch Code ************************************/


void redcallback(double x) {
  if(x > 0)
  {
    digitalWrite(RED_LED,LOW);
    if (! sendPub.publish(setRed, sizeof(setRed)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }
  }
  else{
    digitalWrite(RED_LED,HIGH);
    if (! sendPub.publish(clearRed, sizeof(clearRed)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }

  }
}

void bluecallback(double x) {
  if(x > 0)
  {
    digitalWrite(BLUE_LED,LOW);
    if (! sendPub.publish(setBlue, sizeof(setBlue)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }

  }
  else{
    digitalWrite(BLUE_LED,HIGH);
    if (! sendPub.publish(clearBlue, sizeof(clearBlue)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }

  }
}


void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  pinMode(BLUE_LED,OUTPUT);
  pinMode(RED_LED,OUTPUT);
  
  
  digitalWrite(BLUE_LED,LOW);
  digitalWrite(RED_LED,LOW);

  
  red.setCallback(redcallback);
  blue.setCallback(bluecallback);
  
  
  // Setup MQTT subscription for RED and BLUE led.
  
  mqtt.subscribe(&red);
  mqtt.subscribe(&blue);
  

}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets and callback em' busy subloop
  // try to spend your time here:
  mqtt.processPackets(10000);
  
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 10 seconds...");
       mqtt.disconnect();
       delay(10000);  // wait 10 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
