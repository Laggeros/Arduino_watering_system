#include "convertToPercent.h"

int sensors[6] = {A0, A1, A2, A3, A6, A7}; //Analog inputs on board
int sensorValue; 
int percentSensorValue;

int readSoilMoisture(int sensor){
  //Averaging 10 readings to reduce error possibility
  
  for (int j = 0; j < 10; j++) {  
    sensorValue = sensorValue + analogRead(sensors[sensor]); 
    delay(5); 
  }
  
  sensorValue = sensorValue/10; 
  Serial.print("Sensor analog value: ");
  Serial.println(sensorValue);
  Serial.print("Sensor value: ");
  percentSensorValue = convertToPercent(sensorValue, sensor);
  Serial.print(percentSensorValue);Serial.println("%");
  
  lcd.clear();
  lcd.print("Pot number ");
  lcd.print(sensor);
  lcd.setCursor(0,1);
  lcd.print("Moisture: "); 
  lcd.setCursor(11,1);
  lcd.print("    ");
  lcd.setCursor(11,1);
  lcd.print(percentSensorValue); 
  lcd.print("%");

  return percentSensorValue;
  sensorValue = 0;
}
