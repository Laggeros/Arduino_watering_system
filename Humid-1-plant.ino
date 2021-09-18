#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include "readSoilHumidity.h"

#define inputCLK 2
#define inputDT 3
#define inputBT 4
#define outputPump 5

int counter;
int currentStateCLK;
int previousStateCLK; 
unsigned long lastButtonPress = 0;
int humidityLevel = 50;
bool humiditySelected = false;
int checkInterval = 1;
bool intervalSelected = false;

void setup(){
  Serial.begin(9600); 
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(0,0);

  lcd.print("System");
  lcd.setCursor(0,1);
  lcd.print("starting...");
  delay(2000);

//  if (!bme.begin(0x76)) {
//    Serial.println("Could not find a valid BME280 sensor, check wiring!");
//    while (1);
//  } 
  
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  pinMode (inputBT, INPUT_PULLUP);
  pinMode (outputPump, OUTPUT);

  previousStateCLK = digitalRead(inputCLK);

  Serial.println("Select humidity level:");
  lcd.clear();
  lcd.println("Select humidity level:");
  lcd.setCursor(6,1);
  lcd.print(humidityLevel); lcd.print("%");
  counter = 50;
  while(humiditySelected == false){
    int previousCounter = counter;
    select("humid");
    if(counter != previousCounter){
      lcd.setCursor(9,1);
      lcd.print(" ");
      lcd.setCursor(8,1);
      lcd.print(" ");
      lcd.setCursor(6,1);
      lcd.print(counter);lcd.print("%");
    }
  }
  delay(500);
  Serial.println("Select interval:");
  lcd.clear();
  lcd.println("Select interval:");
  lcd.setCursor(6,1);
  lcd.print(checkInterval); lcd.print("h");
  counter = 1;
  while(intervalSelected == false){
    int previousInterval = counter;
      select("interval");
    if(counter != previousInterval){
      lcd.setCursor(9,1);
      lcd.print(" ");
      lcd.setCursor(8,1);
      lcd.print(" ");
      lcd.setCursor(6,1);
      lcd.print(counter);lcd.print("h");
    }
  }
  detachInterrupt(digitalPinToInterrupt(inputCLK));
  detachInterrupt(digitalPinToInterrupt(inputDT));
  Serial.print("Humidity level: "); Serial.print(humidityLevel); Serial.println("%");
  lcd.clear();
  lcd.print("Beggining to");
  lcd.setCursor(0,1);
  lcd.print("monitor soil...");
  delay(2000);
  lcd.clear();
}

void loop() {
  if(readSoilHumidity() < humidityLevel){
    runPump(outputPump);
  }

  delay(5000); 
}

void select(String type){
  int btnState = digitalRead(inputBT);
  if(type == "humid"){
      attachInterrupt(digitalPinToInterrupt(inputCLK), updateEncoderHumid, CHANGE);
      attachInterrupt(digitalPinToInterrupt(inputDT), updateEncoderHumid, CHANGE);
    if (btnState == LOW) {
      if (millis() - lastButtonPress > 50) {
        humidityLevel = counter;
        humiditySelected = true;
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

void updateEncoderHumid(){
  currentStateCLK = digitalRead(inputCLK);
  if (currentStateCLK != previousStateCLK && currentStateCLK == 1){ 
     if (digitalRead(inputDT) != currentStateCLK) { 
      counter = counter -5;
     } 
     else {
      counter = counter +5;
     }
     if(counter > 100){counter = 100;}
     if(counter < 0) {counter = 0;} 
     Serial.print(counter);
     Serial.println("%");
   } 
   previousStateCLK = currentStateCLK; 
   delay(5);
}

void updateEncoderInterval(){
  currentStateCLK = digitalRead(inputCLK);
  if (currentStateCLK != previousStateCLK && currentStateCLK == 1){ 
     if (digitalRead(inputDT) != currentStateCLK) { 
      counter --;
     } 
     else {
      counter ++;
     }
     if(counter > 24){counter = 24;}
     if(counter < 0) {counter = 0;} 
     Serial.print(counter);
     Serial.println("h");
   } 
   previousStateCLK = currentStateCLK; 
   delay(5);
}

void runPump(int pump){
  Serial.print("Watering...");
  lcd.setCursor(0,1);
  lcd.print("Watering...");
  digitalWrite(pump, HIGH);
  delay(1000);
  digitalWrite(pump, LOW);
  lcd.setCursor(0,1);
  lcd.print("           ");
}
