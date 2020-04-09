/**
 *Author: Max
 *Co-Authors:
 *Date of generation: 20/04/03
 *Date of  update: 20/04/03
 *Code Properties: Code controlling the moisture sensor.
*/

float draughtThreshhold; //0.0-1.0
float moistureThreshhold; //0.0-1.0
float currentMoisture;

/**
* Gets the current moisture in the plant
*
* @return float value between 0 and 1 indicating the percentage of wetness.
* 1 means 100% wet and 0 means that it is completly dry.
*/
float getMoisture(){
  currentMoisture = ADC_raw[moistureSensorPinIndex]/4095.0;
	if(currentMoisture < 0)
		currentMoisture = 0;
	else if(currentMoisture > 1)
		currentMoisture = 1;
	return currentMoisture;
}

/*
  Gets the threshhold for moisture, the moisture that we do not want to
  go over. This is the number where the waterer stops watering.

  @return returns the current moistureThreshhold which is a float value between 0 and 1.
*/
float getMoistureThreshhold(){
  if(moistureThreshhold >= 0 && moistureThreshhold <= 1){
    return moistureThreshhold;
  }
  else{
    return -1;
  }
}

/*
  Sets the threshhold for moisture, the moisture that we do not want to
  go over. This is the number where the waterer stops watering.

  @param moisture is a float value between 0 and 1 to sets the moistureThreshhold.
*/
void setMoistureThreshhold(float newMoisture){
  if(newMoisture >= 0 && newMoisture <= 1){
    moistureThreshhold = newMoisture;
  }
}

/*
  Gets the threshhold for draught, the draughtness level that decides when to water.
  If the moisture of the plant goes below the draughtness level, the controller will
  call the waterpump to water the plant.

  @return returns the current draughtThreshhold which is a float value between 0 and 1.
*/
float getDraughtThreshhold(){
  if(draughtThreshhold >= 0 && draughtThreshhold <= 1){
    return draughtThreshhold;
  }
  else{
    return -1;
  }
}

/*
  Sets the threshhold for draught, the draughtness level that decides when to water.
  If the moisture of the plant goes below the draughtness level, the controller will
  call the waterpump to water the plant.

  @param the new draughtThreshhold which is a float value between 0 and 1.
*/
void setDraughtThreshhold(float newDraught){
  if(newDraught >= 0 && newDraught <= 1){
    draughtThreshhold = newDraught;
  }
}


/*
  Test function used to test that functions work propetly.

  @return an integer to signalize which test that failed. returns 0 if all tests were successful.
*/
int moistureTest(){
  setMoistureThreshhold(0);
  if(getMoistureThreshhold() != 0){
    return 1;
  }
  setMoistureThreshhold(1);
  if(getMoistureThreshhold() != 1){
    return 2;
  }
  setMoistureThreshhold(0.5);
  if(getMoistureThreshhold() != 0.5){
    return 3;
  }
  setMoistureThreshhold(-1);
  if(getMoistureThreshhold() < 0){
    return 4;
  }
  setMoistureThreshhold(2);
  if(getMoistureThreshhold() > 1){
    return 5;
  }



  setDraughtThreshhold(0);
  if(getDraughtThreshhold() != 0){
    return 6;
  }
  setDraughtThreshhold(1);
  if(getDraughtThreshhold() != 1){
    return 7;
  }
  setDraughtThreshhold(0.5);
  if(getDraughtThreshhold() != 0.5){
    return 8;
  }
  setDraughtThreshhold(-1);
  if(getDraughtThreshhold() < 0){
    return 9;
  }
  setDraughtThreshhold(2);
  if(getDraughtThreshhold() > 1){
    return 10;
  }

  //return 0 means no error.
  return 0;
}
