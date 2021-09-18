#include "convertToPercent.h"
#define SensorPin A0 

int sensorValue = 0; 
int percentSensorValue;

int readSoilHumidity(){
  for (int i = 0; i < 10; i++) { 
    sensorValue = sensorValue + analogRead(SensorPin); 
    delay(3); 
  }

 sensorValue = sensorValue/10; 
 Serial.print("Sensor analog value: ");
 Serial.println(sensorValue);
 Serial.print("Sensor value: ");
 percentSensorValue = convertToPercent(sensorValue);
 Serial.print(percentSensorValue);Serial.println("%");

 lcd.clear();
 lcd.print("Soil humid:"); 
 lcd.setCursor(11,0);
 lcd.print("    ");
 lcd.setCursor(11,0);
 lcd.print(percentSensorValue); 
 lcd.print("%");
 
 return percentSensorValue;
 sensorValue = 0;
}
