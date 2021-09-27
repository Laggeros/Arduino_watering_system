const int moistSoilValue = 340; //Calibrate for 100% moist soil 
const int drySoilValue = 93; //Calibrate for 0% moist soil 

//Function that convert analog input from sensor to percentage value using calibrated variables

int convertToPercent(int value){
  int percentValue = 0;
  percentValue = map(value, moistSoilValue, drySoilValue, 0, 100);
  if (percentValue > 100) percentValue = 100;
  if (percentValue < 0) percentValue = 0;
  value = 0;
  return percentValue;
}
