#include "convertToPercent.h"
#define SensorPin A0 

int sensorValue = 0; 

int readSoilHumidity(){
  for (int i = 0; i < 10; i++) { 
    sensorValue = sensorValue + analogRead(SensorPin); 
    delay(3); 
  }

 sensorValue = sensorValue/10; 
 Serial.println(sensorValue);

 lcd.clear();
 lcd.print("Soil humid:"); 
 lcd.setCursor(11,0);
 lcd.print("    ");
 lcd.setCursor(11,0);
 lcd.print(convertToPercent(sensorValue)); 
 lcd.print("%");
 
 return convertToPercent(sensorValue);
 sensorValue = 0;
}
