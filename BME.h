#include <Adafruit_BME280.h>
Adafruit_BME280 bme;

int BME(){
  Serial.print(F("Temperature = "));
    Serial.print(bme.readTemperature());
    Serial.println(" *C");
    lcd.setCursor(0,1);lcd.print("T:");lcd.print(bme.readTemperature()); lcd.print(" ");

    Serial.print(F("Pressure = "));
    Serial.print(bme.readPressure()/100);
    Serial.println(" hPa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bme.readAltitude(1019.66)); 
    Serial.println(" m");

    Serial.print(F("Humidity = "));
    Serial.print(bme.readHumidity());
    Serial.println(" %");
    lcd.print("H:"); lcd.print(bme.readHumidity()); lcd.print("%"); 

    Serial.println();
}
