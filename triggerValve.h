/*
 * Function that closes the valves for specific pot.
 * In case of malfunction try to change LOW to HIGH or reverse.
 */

int valves[6] = {7,8,9,10,11,12}; // Digital outputs on board

void triggerValve(int valve, bool state){
  if(state == true){
    Serial.print("Opening valve number: ");Serial.println(valve);
    digitalWrite(valves[valve-1], HIGH);
    delay(50);
  }
  else if(state == false){
    Serial.print("Closing valve number: ");Serial.println(valve);
    digitalWrite(valves[valve-1], LOW);
    delay(50);
  }
}
