void runPump(int pump, int time){
  if(pumpOn == true){
    int runTime = ((time*1000)/4);
    Serial.println("Watering...");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.print("Watering");
    digitalWrite(pump, LOW);
    delay(runTime);
    lcd.print(".");
    delay(runTime);
    lcd.print(".");
    delay(runTime);
    lcd.print(".");
    delay(runTime);
    digitalWrite(pump, HIGH);
    lcd.setCursor(0,1);
    lcd.print("           ");
    delay(50);
  }
}
