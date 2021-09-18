void runPump(int pump, int time){
  int runTime = ((time*1000)/4);
  Serial.println("Watering...");
  lcd.setCursor(0,1);
  lcd.print("Watering");
  digitalWrite(pump, HIGH);
  delay(runTime);
  lcd.print(".");
  delay(runTime);
  lcd.print(".");
  delay(runTime);
  lcd.print(".");
  delay(runTime);
  digitalWrite(pump, LOW);
  lcd.setCursor(0,1);
  lcd.print("           ");
}