#include <ESP8266WiFi.h>
#include <BH1750FVI.h>
#include <Wire.h>
#include <math.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID       "TTLab"
#define WLAN_PASS       "a4fg72jk99l1mn"
#define AIO_SERVER      "192.168.2.108"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "ubuntu"
#define AIO_KEY         "tvtatk2018"

BH1750FVI LightSensor;

const double timerValue = 10000;
const int sensor = A0;
const int tempSenVolt = 14;
const int soilSenVolt = 12;

unsigned long timer = 0;
float sensorValue = 0;
float voltage = 0;
float temp = 0;
int lux;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe Kosteus = Adafruit_MQTT_Subscribe(&mqtt, "Kosteus");
Adafruit_MQTT_Subscribe Lampo = Adafruit_MQTT_Subscribe(&mqtt, "Lampo");
Adafruit_MQTT_Subscribe Valo = Adafruit_MQTT_Subscribe(&mqtt, "Valo");
Adafruit_MQTT_Subscribe paivitaSensori = Adafruit_MQTT_Subscribe(&mqtt, "paivitaSensori");

Adafruit_MQTT_Publish sendPubKosteus = Adafruit_MQTT_Publish(&mqtt, "Kosteus");
Adafruit_MQTT_Publish sendPubLampo = Adafruit_MQTT_Publish(&mqtt, "Lampo");
Adafruit_MQTT_Publish sendPubValo = Adafruit_MQTT_Publish(&mqtt, "Valo");

void Lammonlahetys() {
    digitalWrite(tempSenVolt, HIGH);
    delay(500);
    sensorValue = analogRead(sensor);
    voltage = sensorValue/1096 * 1;
    temp = (voltage-0.5)/0.01;
    float rounded = roundf(temp * 10)/10;
    //Serial.print(rounded);
    delay(500);
    digitalWrite(tempSenVolt, LOW);
    Serial.print("temperature = ");
    Serial.print(rounded); 
    //lahetaLampo = temp;
    if (! sendPubLampo.publish(rounded, sizeof(rounded)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }
}

void Kosteudenlahetys() {
    digitalWrite(soilSenVolt, HIGH);
    delay(500);
    sensorValue = analogRead(sensor);
    sensorValue = map(sensorValue,590,8,100,0);
    delay(500);
    digitalWrite(soilSenVolt, LOW);
    Serial.print("moisture = ");
    Serial.print(sensorValue, 0);
    Serial.println(" %");
    //lahetaKosteus[] = sensorValue;
    if (! sendPubKosteus.publish(sensorValue, sizeof(sensorValue)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }
}

void Valonlahetys() {
    lux = LightSensor.getAmbientLight();
    Serial.print(lux);
    Serial.print(" lux  ");
    if (! sendPubValo.publish(lux, sizeof(lux)))
        Serial.println(F("Publish Failed."));
    else {
        Serial.println(F("Publish Success!"));
    }  
}

void sensoriCallBack(double x){
  if(x > 0){
    Serial.println("toimii");
    sendPubKosteus.publish(sensorValue, sizeof(sensorValue));
    sendPubValo.publish(lux, sizeof(lux));
    sendPubLampo.publish(temp, sizeof(temp));
  }
  
}

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println(F("Adafruit MQTT demo"));
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

  timer = millis();
  
  paivitaSensori.setCallback(sensoriCallBack);
  Wire.pins(4, 5);
  LightSensor.begin();
  LightSensor.setMode(Continuously_High_Resolution_Mode);
  pinMode(tempSenVolt, OUTPUT);
  pinMode(soilSenVolt, OUTPUT);
  
  mqtt.subscribe(&Valo);
  mqtt.subscribe(&Kosteus);
  mqtt.subscribe(&Lampo);
  mqtt.subscribe(&paivitaSensori);
}

uint32_t x=0;

void loop() {
  MQTT_connect();
  mqtt.processPackets(10000);
  
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  if(millis() - timer > timerValue){
    Lammonlahetys();
    Kosteudenlahetys();
    Valonlahetys();
    timer = millis();
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
