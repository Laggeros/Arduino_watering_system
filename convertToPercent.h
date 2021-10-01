/*
 * Function that convert analog input from sensor to percentage value using calibrated variables
 */

const int moistSoilValue = 520; //Calibrate for 100% moist soil 
const int drySoilValue = 176; //Calibrate for 0% moist soil 

const int calibrationSettings[6][2] = 
  {
    {520, 176}, //1 Sensor
    {520, 176}, //2 Sensor
    {520, 176}, //3 Sensor 
    {520, 176}, //4 Sensor
    {520, 176}, //5 Sensor
    {520, 176}  //6 Sensor
  };

int convertToPercent(int value, int sensor){
  int percentValue = 0;
  percentValue = map(value, calibrationSettings[sensor][0], calibrationSettings[sensor][1], 0, 100);
  if (percentValue > 100) percentValue = 100;
  if (percentValue < 0) percentValue = 0;
  value = 0;
  return percentValue;
}
