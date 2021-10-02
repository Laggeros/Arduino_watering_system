/*
 * Function that closes the valves for specific pot.
 * In case of malfunction try to change LOW to HIGH or reverse.
 */

int valves[6] = {9, 10, 11, 12, 7, 8}; // Digital outputs on board

void triggerValve(int valve, bool state){
  if(state == true){
    Serial.print("Opening valve number: ");Serial.println(valve);
    if(valvesNC == false) digitalWrite(valves[valve-1], HIGH);
    else digitalWrite(valves[valve-1], LOW);
  }
  else if(state == false){
    Serial.print("Closing valve number: ");Serial.println(valve);
    if(valvesNC == false) digitalWrite(valves[valve-1], LOW);
    else digitalWrite(valves[valve-1], HIGH);
  }
}
