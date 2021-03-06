/**
 *  Arduino watering system for plants
 *  
 *  On startup user is asked to set desired moisture level in percent
 *  and time interval in which device will check. 
 *  After that moisture level is check using probe and while
 *  specific valve remain open water pump is turned on for a few
 *  seconds to water the soil. When all the pots are checked and watered
 *  the device goes into sleep mode for time specified in the beggining. 
 *  
 *  Settings:
 *  
 *  1. Select number of sensors in your project (max is 7 for arduino nano).
 *  2. Select time to run your pump (depends on the lenght of the hose).
 *  3. Calibrate moinsture sensors in convertToPercent file. 
 *  4. Select analog inputs for sensors in readSoilMoisture file. 
 *  5. Select digital outputs for valves in triggerValve file. 
 *  6. Change digital inputs for encoder and button if needed in settings of this file. 
 *  
 *  WARNING: 
 *  The code is witten for LOW triggered relay boards.  
 *  If you use normalny closed valves change that in options.
 *  Arduino nano will handle 3 valves when LCD is connected to it so
 *  try to power everything with external power supply. 
 *  
 *  Pinout is default for Arduino nano
 *  
 *  Author: Michał Warchoł
 *  https://github.com/Laggeros
 *  lagger.exe@gmail.com
 *  
 *  Created on: Aug 6, 2021
 */

//Settings

const bool debug = true; //Turns off moisture, pots and interval selection and sets cycle time to 3 sec. 
const bool beeperOn = true;
const bool pumpOn = true;
const bool valvesNC = false; 
const int numberOfSensors = 3;
const int timeToRunThePump = 2;
const int moistureIncrement = 5;

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); //Size of LCD screen

#define outputPump 5
#define beeper 6
#define inputCLK 2 //Digital inputs for encoder
#define inputDT 3 //
#define inputBT 4 //Digital input for button

//End of settings

#include "readSoilMoisture.h"
#include "select.h";
#include "runPump.h";
#include "triggerValve.h";

int cycleCounter;
int error = 0;
int moistureSensor;
int lastMoistureSensor[numberOfSensors];
void(* resetFunc) (void) = 0;

void setup(){
  if(numberOfSensors > 1){
    for(int i = 0; i < numberOfSensors; i++){
      pinMode(valves[i], OUTPUT);
      //Closes all valves when using normally openeded ones
      if(valvesNC == false) digitalWrite(valves[i], LOW); 
      delay(50);
    }
  }
  
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  pinMode (inputBT, INPUT_PULLUP);
  pinMode (beeper, OUTPUT);
  pinMode (outputPump, OUTPUT);
  digitalWrite(outputPump, HIGH);

  previousStateCLK = digitalRead(inputCLK);
  
  Serial.begin(9600); 
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(0,0);

  Serial.println("System starting");
  lcd.print("System");
  lcd.setCursor(0,1);
  lcd.print("starting");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);

  //Pots number selection

  Serial.println("Select number of pots:");
  lcd.clear();
  lcd.print("Select pots:");
  lcd.setCursor(0,1);
  lcd.print("pots: ");
  lcd.setCursor(5,1);
  lcd.print(potNumber);
  counter = 4; //Default moisture level

  while(potsSelected == false){
    int previousCounter = counter;
    select("pots");
    if(counter != previousCounter){
      lcd.setCursor(5,1);
      lcd.print(counter);
    }
    if(millis() > 300000){ //Reset the machine if idle for 5 minutes
      beep(0.5);
      beep(0.5);
      beep(0.5);
      resetFunc(); 
    } 
  }

  Serial.println("Select moisture level:");
  lcd.clear();
  lcd.print("Select moisture");
  lcd.setCursor(0,1);
  lcd.print("level: ");
  lcd.setCursor(6,1);
  lcd.print(moistureLevel); lcd.print("%");
  counter = 50; //Default moisture level

  //Moisture selection 
  
  while(moistureSelected == false){
    int previousCounter = counter;
    select("moisture");
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
  lcd.print("Select check");
  lcd.setCursor(0,1);
  lcd.print("interval:");
  lcd.setCursor(9,1);
  lcd.print(checkInterval); lcd.print("h");
  counter = 1; //Default interval

  //Time interval selection 
  
  while(intervalSelected == false){
    int previousInterval = counter;
    select("interval");
    if(counter != previousInterval){
      lcd.setCursor(12,1);
      lcd.print(" ");
      lcd.setCursor(11,1);
      lcd.print(" ");
      lcd.setCursor(9,1);
      lcd.print(counter);lcd.print("h");
    }
  }
  
  detachInterrupt(digitalPinToInterrupt(inputCLK));
  detachInterrupt(digitalPinToInterrupt(inputDT));
  
  Serial.print("Moisture level: "); Serial.print(moistureLevel); Serial.println("%");
  lcd.clear();
  lcd.print("Beggining to");
  lcd.setCursor(0,1);
  lcd.print("monitor soil...");
  delay(2000);
  lcd.clear();
}

void loop() {
  Serial.println();Serial.print("Cycle number: ");Serial.println(cycleCounter);Serial.println();
  Serial.println("Waking up from idle");
  lcd.clear();
  delay(50);
  lcd.setBacklight(HIGH);
  delay(500);

  if(valvesNC == false) triggerValves("close");
  
  if(error == 1 && debug == false){ //Error hanlder
    Serial.println("Error");
    lcd.print("Error...");
    beep(0.5);
    beep(0.5);
    beep(0.5);
    delay(3600000);
  }

  //Moisture reading of all the sensors
  
  else{
    for(int i = 1; i <= potNumber; i++){
      moistureSensor = readSoilMoisture(i);

      //This section checks if sensor readout is not lover that a reading from 1h ago
      
      if(moistureSensor < lastMoistureSensor[i-1] && checkInterval == 1 && debug == false){
        Serial.println("Check wiring or tube!");
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Check wiring");
        lcd.setCursor(0,1);
        lcd.print("or tube!");
        beep(0.5);
        beep(0.5);
        beep(0.5);
        error = 1;
        lastMoistureSensor[i-1] = 0;
      }
      else{
        delay(3000);
        if(moistureSensor < moistureLevel || debug == true){
          if(numberOfSensors > 1){
            triggerValve(i, true);
            runPump(outputPump, timeToRunThePump);
            triggerValve(i, false);
          }
          else runPump(outputPump, timeToRunThePump);
          delay(1000);
        }
      }
    delay(100);
  }
  
  delay(2000);
  Serial.println("Idle...");Serial.println(" ");
  lcd.clear();
  lcd.print("Idle...");
  delay(2000);

  if(valvesNC == false) triggerValves("open");
  
  lcd.setBacklight(LOW);
  cycleCounter++;
  if(debug == false) delay(checkInterval * 3600000); 
  else delay(3000);
  }
}

void beep(int ms){
  if(beeperOn == true){
    digitalWrite(beeper, HIGH);
    delay(ms *1000);
    digitalWrite(beeper, LOW);
  }
}

void triggerValves(String type){
  for(int i = 0; i < numberOfSensors; i++){
    if(type == "open") digitalWrite(valves[i], HIGH);
    else digitalWrite(valves[i], LOW);
    delay(50);
  }
}
