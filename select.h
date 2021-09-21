#include "updateEncoder.h";

#define inputCLK 2
#define inputDT 3
#define inputBT 4

unsigned long lastButtonPress = 0;
int moistureLevel = 50;
bool moistureSelected = false;
int checkInterval = 1;
bool intervalSelected = false;

void select(String type){
  int btnState = digitalRead(inputBT);
  if(type == "moisture"){
      attachInterrupt(digitalPinToInterrupt(inputCLK), updateEncoderMoisture, CHANGE);
      attachInterrupt(digitalPinToInterrupt(inputDT), updateEncoderMoisture, CHANGE);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        moistureLevel = counter;
        moistureSelected = true;
        Serial.println("Button pressed!");
      }
      lastButtonPress = millis();
    }
  }
  else if(type == "interval"){
      attachInterrupt(digitalPinToInterrupt(inputCLK), updateEncoderInterval, CHANGE);
      attachInterrupt(digitalPinToInterrupt(inputDT), updateEncoderInterval, CHANGE);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        checkInterval = counter;
        intervalSelected = true;
        Serial.println("Button pressed!");
      }
      lastButtonPress = millis();
    }
  }
}
