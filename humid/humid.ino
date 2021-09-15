#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <Adafruit_BME280.h>
Adafruit_BME280 bme;
#include "BME.h"
#include "readSoilHumidity.h"

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
