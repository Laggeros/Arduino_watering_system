/*
 * Function that runs the pump for desired time. 
 * In case of malfunction try to change LOW to HIGH or reverse.
 */

void runPump(int pump, int time){
  int runTime = ((time*1000)/4);
  Serial.println("Watering...");
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print("Watering");
  if(pumpOn == true) digitalWrite(pump, LOW);
  delay(runTime);
  lcd.print(".");
  delay(runTime);
  lcd.print(".");
  delay(runTime);
  lcd.print(".");
  delay(runTime);
  if(pumpOn == true) digitalWrite(pump, HIGH);
  delay(50);
  lcd.setCursor(0,1);
  lcd.print("           ");
  delay(50);
  if(pumpOn == true) delay(2000);
}
