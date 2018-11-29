#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "TTLab"
#define WLAN_PASS       "a4fg72jk99l1mn"
#define AIO_SERVER      "192.168.2.108"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "ubuntu"
#define AIO_KEY         "tvtatk2018"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Kosteus = Adafruit_MQTT_Subscribe(&mqtt, "Kosteus");
Adafruit_MQTT_Subscribe Lampo = Adafruit_MQTT_Subscribe(&mqtt, "Lampo");
Adafruit_MQTT_Subscribe Valo = Adafruit_MQTT_Subscribe(&mqtt, "Valo");

Adafruit_MQTT_Publish sendPub = Adafruit_MQTT_Publish(&mqtt, "Sensorit");

uint8_t lahetaLampo[] = "10";
uint8_t lahetaKosteus[] = "20";
uint8_t lahetaValo[] = "30";

void Lammonlahetys(double x) {
  if(x > 0)
  {
    if (! sendPub.publish(lahetaLampo, sizeof(lahetaLampo)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }
  }
  else{
        Serial.println(F("Publish Failed."));
    }
}

void Kosteudenlahetys(double x) {
  if(x > 0)
  {
    if (! sendPub.publish(lahetaKosteus, sizeof(lahetaKosteus)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }
  }
  else{
        Serial.println(F("Publish Failed."));
    }
}

void Valonlahetys(double x) {
  if(x > 0)
  {
    if (! sendPub.publish(lahetaValo, sizeof(lahetaValo)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }
  }
  else{
        Serial.println(F("Publish Failed."));
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


  Kosteus.setCallback(Kosteudenlahetys);
  Valo.setCallback(Valonlahetys);
  Lampo.setCallback(Lammonlahetys);
  
  
  mqtt.subscribe(&Valo);
  mqtt.subscribe(&Kosteus);
  mqtt.subscribe(&Lampo);
  

}

uint32_t x=0;

void loop() {
  MQTT_connect();
  mqtt.processPackets(10000);
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

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
