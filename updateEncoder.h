#define inputCLK 2
#define inputDT 3

int currentStateCLK;
int previousStateCLK;
int counter; 

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
     if(counter < 1) {counter = 1;} 
     Serial.print(counter);
     Serial.println("h");
   } 
   previousStateCLK = currentStateCLK; 
   delay(5);
}