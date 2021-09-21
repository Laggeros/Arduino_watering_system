#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include "readSoilHumidity.h"
#include "select.h";
#include "runPump.h";

#define outputPump 5
#define beeper 6

int error = 0;
int humidSensor;
int lastHumidSensor;
void(* resetFunc) (void) = 0;

void setup(){
  pinMode (inputCLK,INPUT);
  pinMode (inputDT,INPUT);
  pinMode (inputBT, INPUT_PULLUP);
  pinMode (outputPump, OUTPUT);
  pinMode (beeper, OUTPUT);

  previousStateCLK = digitalRead(inputCLK);
  
  Serial.begin(9600); 
  lcd.init();                  
  lcd.backlight();
  lcd.setCursor(0,0);

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

  Serial.println("Select humidity level:");
  lcd.clear();
  lcd.print("Select humidity");
  lcd.setCursor(0,1);
  lcd.print("level: ");
  lcd.setCursor(6,1);
  lcd.print(humidityLevel); lcd.print("%");
  counter = 50; //Default humidity level
  
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
    if(millis() > 300000){
      beep(0.5);
      beep(0.5);
      beep(0.5);
      resetFunc();
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
  
  Serial.print("Humidity level: "); Serial.print(humidityLevel); Serial.println("%");
  lcd.clear();
  lcd.print("Beggining to");
  lcd.setCursor(0,1);
  lcd.print("monitor soil...");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.clear();
  delay(50);
  lcd.setBacklight(HIGH);
  if(error == 1){
    lcd.print("Error...");
    beep(0.5);
    beep(0.5);
    beep(0.5);
    delay(3600000);
  }
  else{
    humidSensor = readSoilHumidity();
    if(humidSensor < lastHumidSensor && checkInterval == 1){
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
      lastHumidSensor = 0;
    }
  else{
    if(humidSensor < humidityLevel){
      runPump(outputPump, 2);
    }
  }
  
  delay(2000);
  Serial.println("Idle...");Serial.println(" ");
  lcd.clear();
  lcd.print("Idle...");
  delay(2000);
  lcd.setBacklight(LOW);
  //delay(checkInterval * 3600000); 
  delay(3000);
  }
}

void beep(int ms){
//  digitalWrite(beeper, HIGH);
//  delay(ms *1000);
//  digitalWrite(beeper, LOW);
}
