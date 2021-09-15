const int AirValue = 520; 
const int WaterValue = 176;

int convertToPercent(int value){
  int percentValue = 0;
  percentValue = map(value, AirValue, WaterValue, 0, 100);
  if (percentValue > 100) percentValue = 100;
  if (percentValue < 0) percentValue = 0;
  value = 0;
  return percentValue;
}
