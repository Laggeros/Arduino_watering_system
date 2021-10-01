#include "updateEncoder.h";

unsigned long lastButtonPress = 0;
int moistureLevel = 50;
int checkInterval = 1;
bool moistureSelected;
bool intervalSelected;


void select(String type){
  if(debug == true){
    moistureSelected = true;
    intervalSelected = true;
  }
  else{
    moistureSelected = false;
    intervalSelected = false;
  }

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
