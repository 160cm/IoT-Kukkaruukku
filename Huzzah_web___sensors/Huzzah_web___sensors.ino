#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <BH1750FVI.h>
#include <Wire.h>

BH1750FVI LightSensor;

const int sensor = A0;
const int tempSenVolt = 14;
const int soilSenVolt = 12;

float sensorValue = 0;
float voltage = 0;
float temp = 0;
int lux;

const char* ssid     = "TTLab";
const char* password = "a4fg72jk99l1mn";
const char* host = "172.20.240.56";

void setup() {
  Serial.begin(115200);
  delay(100);
  Wire.pins(4, 5);
  LightSensor.begin();
  LightSensor.setMode(Continuously_High_Resolution_Mode);
  pinMode(tempSenVolt, OUTPUT);
  pinMode(soilSenVolt, OUTPUT);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

 while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 
}

void PostData() {
  String data = "maaper=";
  String sensordata = data + temp;
  String url = "http://172.20.240.56/lisaadata.php";
  HTTPClient http;
  http.setReuse(true);
  http.begin(url);
  http.addHeader("Host", "http://172.20.240.56");
 http.addHeader("User-Agent", "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0");
 http.addHeader("Accept-Language", " en-US,en;q=0.5");
 http.addHeader("Accept-Encoding", " gzip, deflate, br");
  http.addHeader("Content-Type", " application/x-www-form-urlencoded; charset=UTF-8");
 http.addHeader("X-Requested-With", " XMLHttpRequest");
 http.addHeader("Referer", " https://www.shippingmanager.dk/sh/?fb_source=shippingmanager.dk");
 http.addHeader("Connection", "keep-alive");
 http.addHeader("Pragma", " no-cache");
 http.addHeader("Cache-Control", " no-cache");

  int result = http.POST(sensordata);
  http.writeToStream(&Serial);
  http.end();

}

void loop() {
lux = LightSensor.getAmbientLight();
  Serial.print(lux);
  Serial.print(" lux");
  digitalWrite(tempSenVolt, HIGH);
  delay(500);
  sensorValue = analogRead(sensor);
  voltage = sensorValue/1096 * 1;
  temp = (voltage-0.5)/0.01;
  digitalWrite(tempSenVolt, LOW);
  Serial.print("  temperature = ");
  Serial.print(temp, 1); 
  digitalWrite(soilSenVolt, HIGH); 
  delay(500);
  sensorValue = analogRead(sensor);
  sensorValue = map(sensorValue,545,5,100,0);
  digitalWrite(soilSenVolt, LOW);
  Serial.print("  moisture = ");
  Serial.print(sensorValue, 0);
  Serial.println(" %");
  delay(500);
PostData();
 delay(10000);
 
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
}

