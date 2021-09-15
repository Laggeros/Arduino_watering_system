#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;
#include "BME.h"
#define SensorPin A0 

int sensorValue = 0; 
const int AirValue = 520; 
const int WaterValue = 176;


void setup(){
  Serial.begin(9600); 
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(0,0);

  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  } 
}

void loop() {
 readSoilHumidity();

  if (bme.begin(0x76)) {
   BME();
  }
  
 delay(30000); 
}

int readSoilHumidity(){
  for (int i = 0; i < 10; i++) { 
    sensorValue = sensorValue + analogRead(SensorPin); 
    delay(3); 
  } 

 sensorValue = sensorValue/10; 
 Serial.println(sensorValue);

 lcd.print("Soil humid:"); 
 lcd.setCursor(11,0);
 lcd.print("    ");
 lcd.setCursor(11,0);
 lcd.print(convertToPercent(sensorValue)); 
 lcd.print("%");
 
 sensorValue = 0;
}

int convertToPercent(int value){
  int percentValue = 0;
  percentValue = map(value, AirValue, WaterValue, 0, 100);
  if (percentValue > 100) percentValue = 100;
  if (percentValue < 0) percentValue = 0;
  value = 0;
  return percentValue;
}
