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

void setup() {
  Serial.begin(9600);
  Wire.pins(4, 5);
  LightSensor.begin();
  LightSensor.setMode(Continuously_High_Resolution_Mode);
  pinMode(tempSenVolt, OUTPUT);
  pinMode(soilSenVolt, OUTPUT);
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
}
